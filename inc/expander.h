/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:18:00 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/15 11:11:46 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "define.h"
# include "minishell.h"
# include "parser.h"

char		**expander(t_tools *tools, char **str, char **envp);
size_t		dollar_sign(char *str);
char		*char_to_str(char c);
int			after_dol_lenght(char *str, int j);
size_t		quotes_lenght(char *str);
size_t		find_equal(char *str);
size_t		find_dollar(char *str);
int			loop_if_dollar_sign(char **envp, char *str, char **tmp, int j);
int			question_mark(char **tmp);
char	*delete_quotes(char *str, char c);
char	*detect_dollar(char *str, char **envp);


//main_utils
bool		ft_simple_cmdsclear(t_simple_cmds **lst);
void		ft_lexerclear(t_lexer **lst);
void	    ft_nodefirst_cmdsver(t_simple_cmds **node);
int			free_tools(t_tools *tools);
int			implement_tools(t_tools *tools);
int	        count_quotes(char *line);


//グローバル変数(終了ステータス)
extern int	g_status;
void		signal_init(void);
void		sigquit_handler(int sig);
void		sigint_handler(int sig);

#endif
