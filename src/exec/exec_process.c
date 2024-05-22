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
	int		status;
	int		pid;
	int		last_error;
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
	free_pipes(data->pipe_list);
}

void	mark_status(int status, t_data *data, bool *forcequit)
{
	int	term_sig;

	if (WEXITSTATUS(status) != 0 && is_builtin(data) == 0)
		data->last_error = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		term_sig = WTERMSIG(status);
		if (term_sig == SIGQUIT)
		{
			write(2, "Quit (core dumped)", 19);
			data->last_error = 131;
		}
		else if (term_sig == SIGINT)
		{
			data->last_error = 130;
		}
		write(2, "\n", 1);
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
