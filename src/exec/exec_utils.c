/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:04:19 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/28 13:39:29 by nchaize-         ###   ########.fr       */
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

void	exec_real(t_data *data, size_t i)
{
	char	*path;
	char	**new_env;

	path = get_exec_path(data->commands[0], data);
	if (data->fdin != STDIN_FILENO)
		close_safe(data, data->fdin);
	redir_lasterror(data, i);
	if (path == NULL)
		no_path(data, i);
	new_env = recreate_env(data);
	if (new_env == NULL)
		error(data, "Memory allocation failure\n");
	execve(path, data->commands, new_env);
}