/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:52:03 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/14 16:52:03 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_first_command(t_data *data, t_pipe **pipe_list, size_t i)
{
	if (data->n_commands == 1)
	{
		dup2(data->fdin, STDIN_FILENO);
		dup2(data->fdout, STDOUT_FILENO);
		exec(data, i);
	}
	if (data->fdin != STDIN_FILENO)
		dup2(data->fdin, STDIN_FILENO);
	dup2(access_pipe(pipe_list, i)->p[1], STDOUT_FILENO);
}

void	child_process(t_data *data, t_pipe **pipe_list, size_t i)
{
	data->last_error = 0;
	if (i == 0)
		child_first_command(data, pipe_list, i);
	else if (i == data->n_commands - 1)
	{
		if (data->fdout != STDOUT_FILENO)
			dup2(data->fdout, STDOUT_FILENO);
		dup2(access_pipe(pipe_list, i - 1)->p[0], STDIN_FILENO);
	}
	else
	{
		dup2(access_pipe(pipe_list, i - 1)->p[0], STDIN_FILENO);
		dup2(access_pipe(pipe_list, i)->p[1], STDOUT_FILENO);
	}
	close_pipes(data, pipe_list, data->n_commands - 1, -1);
	exec(data, i);
}

void	parent_process(t_data *data, t_pipe **pipe_list)
{
	int	status;
	int	pid;
	int	last_error;
	bool	forcequit;
	
	last_error = 0;
	forcequit = false;
	close_pipes(data, pipe_list, data->n_commands - 1, -1);
	while (waitpid(-1, &status, 0) != -1)
	{
		mark_status(status, data, &forcequit);
	}
	close_safe(data, access_pipe(pipe_list, data->n_commands - 1)->p[1]);
	if (read((access_pipe(pipe_list, data->n_commands - 1)->p[0]),
			&(last_error), sizeof(int)) == -1)
		return ;
	close_safe(data, access_pipe(pipe_list, data->n_commands - 1)->p[0]);
	if (forcequit == false)
		data->last_error = (int)last_error;
	/*printf("Last error = %d\nData->last_error = %d\n",
		last_error, data->last_error);*/
	free_pipes(data->pipe_list);
}
