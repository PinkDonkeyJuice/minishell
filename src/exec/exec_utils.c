/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:04:19 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/31 12:22:00 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_child_process(t_data *data, t_pipe **pipe_list, size_t i)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	child_process(data, pipe_list, i);
}

void	no_path(t_data *data, size_t i)
{
	free_env(data->env_c);
	if (i != data->n_commands - 1)
		free_pipes(data->pipe_list);
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
	{
		free_env(data->env_c);
		if (i != data->n_commands - 1)
			free_pipes(data->pipe_list);
		if (data->commands == NULL || data->commands[0] == NULL)
			exit(0);
		exit(127);
	}
	new_env = recreate_env(data);
	if (new_env == NULL)
		error(data, "Memory allocation failure\n");
	execve(path, data->commands, new_env);
}
