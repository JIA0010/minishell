/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:17:23 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/28 15:31:32 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_double_operator(t_simple_cmds *new, t_simple_cmds *tmp,
		t_tools *tools)
{
	if (tmp && tmp->redirections && (tmp->redirections->token == SEMICOLON
			|| tmp->redirections->token == AND_AND
			|| tmp->redirections->token == OR_OR
			|| tmp->redirections->token == PIPE))
	{
		if (new->redirections && (new->redirections->token == SEMICOLON
				|| new->redirections->token == AND_AND
				|| new->redirections->token == OR_OR
				|| new->redirections->token == PIPE))
		{
			parser_token_error(tools, new->redirections->token);
			free(tools->str);
			tools->str = NULL;
			ft_simple_cmdsclear(&tools->simple_cmds);
			ft_lexerclear(&tools->lexer_list);
			implement_tools(tools);
			return (false);
		}
	}
	return (true);
}

int	ft_error(int error, t_tools *tools)
{
	tools->error_num = 2;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (error == 0)
		ft_putstr_fd("syntax error near unexpected token `newline'\n",
			STDERR_FILENO);
	else if (error == 1)
		ft_putstr_fd("memory error: unable to assign memory\n", STDERR_FILENO);
	else if (error == 2)
		ft_putstr_fd("syntax error: unable to locate closing quotation\n",
			STDERR_FILENO);
	else if (error == 3)
		ft_putstr_fd("Parser problem\n", STDERR_FILENO);
	else if (error == 4)
		ft_putstr_fd("syntax error: unexpected end of file\n",
			STDERR_FILENO);
	return (EXIT_FAILURE);
}

void	parser_error(int error, t_tools *tools)
{
	free(tools->str);
	ft_simple_cmdsclear(&tools->simple_cmds);
	ft_lexerclear(&tools->lexer_list);
	ft_error(error, tools);
}

int	parser_token_error(t_tools *tools, t_tokens token)
{
	tools->error_num = 2;
	ft_putstr_fd("minishell: syntax error near unexpected token ",
		STDERR_FILENO);
	if (token == GREAT)
		ft_putstr_fd("`>'\n", STDERR_FILENO);
	else if (token == GREAT_GREAT)
		ft_putstr_fd("`>>'\n", STDERR_FILENO);
	else if (token == LESS)
		ft_putstr_fd("`<'\n", STDERR_FILENO);
	else if (token == LESS_LESS)
		ft_putstr_fd("`<<'\n", STDERR_FILENO);
	else if (token == PIPE)
		ft_putstr_fd("`|'\n", STDERR_FILENO);
	else if (token == SEMICOLON)
		ft_putstr_fd("`;'\n", STDERR_FILENO);
	else if (token == AND_AND)
		ft_putstr_fd("`&&'\n", STDERR_FILENO);
	else if (token == OR_OR)
		ft_putstr_fd("`||'\n", STDERR_FILENO);
	else
		ft_putstr_fd("\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	handle_operator_error(t_tools *tools, t_tokens token)
{
	if (token == PIPE)
	{
		parser_token_error(tools, tools->lexer_list->token);
		ft_lexerclear(&tools->lexer_list);
		free(tools->str);
		return (EXIT_FAILURE);
	}
	if (!tools->lexer_list || (tools->lexer_list->str
			&& tools->lexer_list->str[0] == '\0'))
	{
		parser_error(0, tools);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
