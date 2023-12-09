/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 01:18:05 by toshota           #+#    #+#             */
/*   Updated: 2023/11/25 21:43:07 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_builtin_cmd_count(t_pipex *pipex)
{
	int	cmd_i;
	int	builtin_cmd_count;

	cmd_i = 0;
	builtin_cmd_count = 0;
	while (pipex->cmd_absolute_path[cmd_i])
	{
		if (is_cmd_builtin(pipex->cmd_absolute_path[cmd_i]))
			builtin_cmd_count++;
		cmd_i++;
	}
	return (builtin_cmd_count);
}

int	get_pipe_count(char **argv)
{
	int	arg_i;
	int	pipe_count;

	arg_i = 0;
	pipe_count = 0;
	while (argv[arg_i])
	{
		if (is_specified_pipe(argv[arg_i]))
			pipe_count++;
		arg_i++;
	}
	return (pipe_count);
}

static void	malloc_multiple_pipe(char **argv, t_pipex *pipex)
{
	int	i;
	int	pipe_count;

	i = 0;
	pipe_count = get_pipe_count(argv);
	if (pipe_count == 0)
		return ;
	pipex->pipe_fd = \
	(int **)check_malloc(malloc(sizeof(int *) * (pipe_count + 1)));
	while (i < pipe_count)
	{
		pipex->pipe_fd[i] = (int *)check_malloc(malloc(sizeof(int) * 2));
		i++;
	}
	pipex->pipe_fd[i] = NULL;
}

static void	init_pipex(t_pipex *pipex)
{
	ft_bzero(pipex, sizeof(t_pipex));
	pipex->infile_fd = STDIN_FILENO;
	pipex->outfile_fd = STDOUT_FILENO;
}

// #include "expander.h"
// /tmp/here_docファイルがあれば各行に対して変数展開を行う！
// char *get_expanded_line(t_tools *tools, char **heap_envp)
// {
	/*
	expanded_here_docファイルをオープンする
	hare_docの各行がなくなるまで繰り返す
	{
		gnlで1行を取得する
		その行をexpander();で変数展開する
		変数展開した行をexpanded_here_docファイルに追記で出力する
	}
	*/
// }

bool	get_pipex(char **argv, char **heap_envp, t_pipex *pipex)
{
	init_pipex(pipex);
	if (get_cmd_absolute_path(argv, heap_envp, pipex) == false)
		return (false);
	// 「/tmp/here_docg が存在していない場合，proc_here_docを実効する」とすれば proc_here_docg が二重で実行されるのを防げる！
	if (get_infile_fd(pipex, argv, false) == false)
		return (false);
	if (get_outfile_fd(pipex, argv) == false)
		return (false);
	malloc_multiple_pipe(argv, pipex);

	return (true);
}
