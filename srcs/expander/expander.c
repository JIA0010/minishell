/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:39:54 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/15 15:07:00 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"
#include "pipex.h"

char	*detect_dollar(char *str, char **envp)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = 0;
	tmp = ft_strdup("\0");
	while (str[j])
	{
		j += handle_digit_after_dollar(j, str);
		if (str[j] == '$' && str[j + 1] == '?')
			j += question_mark(&tmp);
		else if (title(str, j) == true)
			j += loop_if_dollar_sign(envp, str, &tmp, j);
		else
		{
			tmp2 = char_to_str(str[j++]);
			tmp3 = ft_strjoin(tmp, tmp2);
			free(tmp);
			tmp = tmp3;
			free(tmp2);
		}
	}
	return (tmp);
}

void	ft_nodefirst_for_t_simple_cmds(t_simple_cmds **node)
{
	if (node == NULL || *node == NULL)
		return ;
	while ((*node)->prev != NULL)
		*node = (*node)->prev;
}

void	free_old_str(t_tools *tools)
{
	while (tools->simple_cmds->str)
	{
		all_free_tab(tools->simple_cmds->str);
		tools->simple_cmds->str = NULL;
		if (tools->simple_cmds->next == NULL)
			break ;
		tools->simple_cmds = tools->simple_cmds->next;
	}
	ft_nodefirst_for_t_simple_cmds(&tools->simple_cmds);
}

bool	check_case_herecoc(char **str, int i)
{
	char *tmp;

	if(str[i + 1] &&is_match(str[i], "<<") == true && str[i + 1] != '\0')
	{
		tmp = check_malloc(ft_strdup(str[i]));
		free(str[i]);
		str[i] = tmp;
		tmp = check_malloc(ft_strdup(str[i + 1]));
		free(str[i + 1]);
		str[i + 1] = tmp;
		// i = i + 2;
	}
	return (i);
}

char	**expander(t_tools *tools, char **str, char **envp)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (str[i] != NULL)
	{

		if(check_case_herecoc(str, i) != 0)
			i = i + 2;
		else if (find_dollar(str[i]) != 0 && str[i][find_dollar(str[i]) - 2] != '\''
		&&
		str[i][find_dollar(str[i])] != '\0')
		{
			tmp = detect_dollar(str[i], envp);
			free(str[i]);
			str[i] = tmp;
		}
		i++;
	}
	free_old_str(tools);
	return (str);
}
