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
	if (data->fdin != STDIN_FILENO && data->n_pipe_fdin == 0)
		dup2(data->fdin, STDIN_FILENO);
	dup2(access_pipe(pipe_list, i)->p[1], STDOUT_FILENO);
}

void	child_process(t_data *data, t_pipe **pipe_list, size_t i)
{
	if (i == 0)
		child_first_command(data, pipe_list, i);
	else if (i == data->n_commands - 1)
	{
		if (data->fdout != STDOUT_FILENO)
			dup2(data->fdout, STDOUT_FILENO);
		if (data->fdin != STDIN_FILENO && i == data->n_pipe_fdin)
			dup2(data->fdin, STDIN_FILENO);
		else
			dup2(access_pipe(pipe_list, i - 1)->p[0], STDIN_FILENO);
	}
	else
	{
		if (data->fdin != STDIN_FILENO && i == data->n_pipe_fdin)
			dup2(data->fdin, STDIN_FILENO);
		else
			dup2(access_pipe(pipe_list, i - 1)->p[0], STDIN_FILENO);
		dup2(access_pipe(pipe_list, i)->p[1], STDOUT_FILENO);
	}
	close_pipes(data, pipe_list, data->n_commands - 1, -1);
	exec(data, i);
}

void	parent_process(t_data *data, t_pipe **pipe_list)
{
	int		status;
	int		last_error;
	bool	forcequit;
	pid_t	pid;

	last_error = 0;
	forcequit = false;
	close_pipes(data, pipe_list, data->n_commands - 1, -1);
	pid = waitpid(-1, &status, 0);
	while (pid != -1)
	{
		mark_status(status, data, &forcequit, pid);
		pid = waitpid(-1, &status, 0);
	}
	close_safe(data, access_pipe(pipe_list, data->n_commands - 1)->p[1]);
	if (read((access_pipe(pipe_list, data->n_commands - 1)->p[0]),
			&(last_error), sizeof(int)) == -1)
		return ;
	close_safe(data, access_pipe(pipe_list, data->n_commands - 1)->p[0]);
	if (forcequit == false)
		data->last_error = (int)last_error;
	free_pipes(data->pipe_list);
}

void	mark_status(int status, t_data *data, bool *forcequit, pid_t pid)
{
	int	term_sig;

	if (WEXITSTATUS(status) != 0 && is_builtin(data) == 0
		&& pid == data->last_pid)
	{
		data->last_error = WEXITSTATUS(status);
		*forcequit = true;
	}
	if (WIFSIGNALED(status))
	{
		term_sig = WTERMSIG(status);
		if (term_sig == SIGQUIT && pid == data->last_pid)
		{
			write(2, "Quit (core dumped)\n", 20);
			data->last_error = 131;
		}
		else if (term_sig == SIGINT)
		{
			write(2, "\n", 1);
			if (pid == data->last_pid)
				data->last_error = 130;
		}
		if (pid == data->last_pid)
			*forcequit = true;
	}
}

size_t	count_pipes(t_command *command_list)
{
	size_t	n;
	size_t	i;

	n = 1;
	i = 0;
	if (command_list == NULL)
		return (0);
	while (command_list[i].command != NULL)
	{
		if (command_list[i].type == TYPE_PIPE)
		{
			if (command_list[i + 1].command == NULL)
			{
				printf("Missing command after pipe\n");
				return (0);
			}
			n++;
		}
		i++;
	}
	return (n);
}
