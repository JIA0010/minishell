/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:39:21 by toshota           #+#    #+#             */
/*   Updated: 2023/11/24 00:14:20 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	get_home(char **path_ptr, char **envp)
{
	int	env_i;

	env_i = 0;
	while (envp[env_i] && ft_strncmp(envp[env_i], "HOME=", ft_strlen("HOME=")))
		env_i++;
	if (is_path_found(envp[env_i]) == false)
		return (false);
	*path_ptr = check_malloc(ft_strdup(envp[env_i] + ft_strlen("HOME=")));
	return (true);
}

static bool	is_path_alreadly_absollute_path(char *path)
{
	return (path[0] == '/' && (path[1] == '\0' || ft_strchr(&path[1], '/')));
}

static bool	get_path_from_cmd_arg(char **path_ptr, char **cmd, char ***envp)
{
	char	*tmp;

	if (cmd[1] == NULL || !ft_strncmp(cmd[1], "~/", ft_strlen(cmd[1])))
		return (get_home(path_ptr, *envp));
	else if (cmd[1][0] == '~')
	{
		if (get_home(path_ptr, *envp) == false)
			return (false);
		tmp = *path_ptr;
		*path_ptr = check_malloc(ft_strjoin(*path_ptr, cmd[1]
					+ ft_strlen("~")));
		free(tmp);
	}
	else
		*path_ptr = check_malloc(ft_strdup(cmd[1]));
	return (true);
}

bool	change_current_directory(char ***envp, int env_i, char *path)
{
	int		down_count_from_cwd;
	char	*tmp;

	// cdの引数として渡ってくるpathの末尾が/終わりの場合，末尾の/を取る
	if (ft_strncmp(path, "/", ft_strlen(path)) && path[ft_strlen(path)
		- 1] == '/')
		ft_strlcpy(path, path, ft_strlen(path));
	if (is_path_alreadly_absollute_path(path))
	{
		tmp = path;
		path = check_malloc(ft_strjoin("PWD=", path));
		ft_strlcpy(envp[0][env_i], path, ft_strlen(path) + 1);
	}
	else
	{
		// カレントディレクトリとlsが対応しないため↓の is_file_exist(path) の結果が適切に出ない問題をどうにかする！
		// if (is_file_exist(path) == false)
		// 	return (put_error("-bash: cd: "), put_error(path), put_error(": No such file or directory\n"), free(path), true);
		down_count_from_cwd = get_down_count_from_cwd(path);
		envp[0][env_i] = down_cwd(envp[0][env_i], down_count_from_cwd);
		path = down_passed_path(path, down_count_from_cwd);
		// pathに何か文字が残っていたら/を加えたのちにつなげる
		if (ft_strlen(path))
		{
			tmp = path;
			path = ft_strjoin("/", path);
			free(tmp);
		}
		tmp = path;
		path = check_malloc(ft_strjoin(envp[0][env_i], path));
		ft_strlcpy(envp[0][env_i], path, ft_strlen(path) + 1);
		if (!ft_strncmp(envp[0][env_i], "PWD=", ft_strlen(envp[0][env_i])))
			ft_strlcpy(envp[0][env_i], "PWD=/", ft_strlen("PWD=/") + 1);
	}
	return (free(path), free(tmp), true);
}

int	exec_cd(char **cmd, char ***envp)
{
	int		env_i;
	char	*path;

	env_i = 0;
	while (envp[0][env_i] && ft_strncmp(envp[0][env_i], "PWD=",
			ft_strlen("PWD=")))
		env_i++;
	if (is_path_found(envp[0][env_i]) == false)
		return (false);
	if (get_path_from_cmd_arg(&path, cmd, envp) == false)
		return (free(path), false);
	if (!ft_strncmp(path, ".", ft_strlen(path)) || !ft_strncmp(path, "./",
			ft_strlen(path)))
		return (free(path), true);
	return (change_current_directory(envp, env_i, path));
}
