/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:36:00 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/08 12:57:53 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/expander.h"
#include "../inc/minishell.h"

int	implement_tools(t_tools *tools)
{
	tools->simple_cmds = NULL;
	tools->lexer_list = NULL;
	tools->str = NULL;
	tools->envp = NULL;
	tools->tmp_array = NULL;
	signal_init();
	return (1);
}

int	free_tools(t_tools *tools)
{
	ft_simple_cmdsclear(&tools->simple_cmds);
	free(tools->str);
	all_free_tab(tools->envp);
	implement_tools(tools);
	free(tools);
	return (1);
}

char	**ft_arrdup(char **arr)
{
	char	**rtn;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	rtn = ft_calloc(sizeof(char *), i + 1);
	if (!rtn)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		rtn[i] = ft_strdup(arr[i]);
		if (rtn[i] == NULL)
		{
			all_free_tab(rtn);
			return (rtn);
		}
		i++;
	}
	return (rtn);
}

void	ft_lexerclear(t_lexer **lst)
{
	t_lexer	*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->str)
			free((*lst)->str);
		if (*lst)
			free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void	ft_simple_cmdsclear(t_simple_cmds **simple_cmds)
{
	t_simple_cmds *tmp;
	t_lexer *redirections_tmp;

	if (!*simple_cmds)
		return ;
	while (*simple_cmds)
	{
		tmp = (*simple_cmds)->next;
		redirections_tmp = (*simple_cmds)->redirections;
		ft_lexerclear(&redirections_tmp);
		if ((*simple_cmds)->str)
			all_free_tab((*simple_cmds)->str);
		free(*simple_cmds);
		*simple_cmds = tmp;
	}
	*simple_cmds = NULL;
}