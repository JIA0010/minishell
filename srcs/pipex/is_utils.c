/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/12/01 21:23:30 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	is_specified_redirect(char *str)
{
	return (is_specified_infile(str) || is_specified_here_doc(str)
		|| is_specified_outfile_overwriting(str)
		|| is_specified_outfile_apend(str));
}

bool	is_io_file(char **argv, int arg_i)
{
	return (arg_i > 0 && is_specified_redirect(argv[arg_i - 1]) && argv[arg_i]);
}

bool	is_cmd(char **argv, int arg_i)
{
	if (is_specified_operators(argv[arg_i]) || is_io_file(argv, arg_i))
		return (false);
	return (is_file_exectable(argv[arg_i]) || !is_file_exist(argv[arg_i]));
}

bool	is_cmd_relative_path(char ***cmd_absolute_path, int cmd_i)
{
	return (cmd_absolute_path[0][cmd_i][0] != '/'
		&& ft_strchr(&cmd_absolute_path[0][cmd_i][1], '/'));
}

bool	is_cmd_alreadly_absollute_path(char ***cmd_absolute_path, int cmd_i)
{
	return (cmd_absolute_path[0][cmd_i][0] == '/'
		&& ft_strchr(&cmd_absolute_path[0][cmd_i][1], '/'));
}
