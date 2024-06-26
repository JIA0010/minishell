/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:39:21 by toshota           #+#    #+#             */
/*   Updated: 2023/12/28 16:13:49 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	exec_export(char **cmd, t_env **env, t_pipex *pipex)
{
	int		i;
	int		flag;

	i = 1;
	flag = 1;
	if (cmd[i])
	{
		while (cmd[i] && is_under_bar(cmd[i]) == false)
		{
			if (get_old_env_to_be_updated(cmd[i], *env) == NULL)
				flag *= add_new_value(cmd[i], env, pipex);
			else
				update_value(cmd[i], env);
			ft_nodefirst(env);
			i++;
		}
	}
	else
	{
		get_order(*env);
		show_env(env, pipex);
	}
	return (ft_nodefirst(env), flag);
}
