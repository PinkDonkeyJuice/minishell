/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:04:19 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/28 12:07:05 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_path(t_data *data, size_t i)
{
	free_env(data->env_c);
	if (i != data->n_commands - 1)
		free_pipes(data->pipe_list);
	exit(127);
}

void	was_builtins(t_data *data, size_t i)
{
	free_env(data->env_c);
	redir_lasterror(data, i);
}
