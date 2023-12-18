/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:36:07 by toshota           #+#    #+#             */
/*   Updated: 2023/12/18 23:49:14 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	is_node_first(t_env *node)
{
	return (node->prev == NULL);
}

bool	is_node_last(t_env *node)
{
	return (node->next == NULL);
}

bool	is_node_only_one(t_env *node)
{
	return (is_node_first(node) && is_node_last(node));
}
