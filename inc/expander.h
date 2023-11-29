/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:18:00 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/11/29 15:00:39 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "lexer.h"
# include "parser.h"
# include "minishell.h"

char	**expander(t_tools *tools, char **str);
size_t	dollar_sign(char *str);
char	*char_to_str(char c);
int		after_dol_lenght(char *str, int j);
size_t	quotes_lenght(char *str);
size_t	find_equal(char *str);
size_t	find_dollar(char *str);
int		loop_if_dollar_sign(t_tools *tools, char *str, char **tmp, int j);
int	    question_mark(char **tmp);


//main_utils
char	**	ft_arrdup(char **arr);
void	free_arr(char **split_arr);
void	ft_simple_cmdsclear(t_simple_cmds **lst);
void	ft_lexerclear(t_lexer **lst);

#endif