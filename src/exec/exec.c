/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:26:03 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/03 11:36:40 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_data *data, size_t i)
{
	char	*path;

	free_commands(data->commands);
	data->commands = get_commands(data->command_list, i);
	if (data->commands == NULL)
	{
		printf("Memory allocation problem encountered during get_commands_\n");
		exit(-1);
	}
	data->i_command = i;
	if (check_builtins(data) == 0)
	{
		path = get_exec_path(data->commands[0]);
		if (data->fdin != STDIN_FILENO)
			close_safe(data, data->fdin);
		execve(path, data->commands, data->env);
	}
	exit(1);
}

void	child_first_command(t_data *data, t_pipe **pipe_list, size_t i)
{
	write(1, "a\n", 2);
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
	if (i == 0)
		child_first_command(data, pipe_list, i);
	else if (i == data->n_commands - 1)
	{
		write(1, "c\n", 2);
		if (data->fdout != STDOUT_FILENO)
			dup2(data->fdout, STDOUT_FILENO);
		dup2(access_pipe(pipe_list, i - 1)->p[0], STDIN_FILENO);
	}
	else
	{
		write(1, "b\n", 2);
		dup2(access_pipe(pipe_list, i - 1)->p[0], STDIN_FILENO);
		dup2(access_pipe(pipe_list, i)->p[1], STDOUT_FILENO);
	}
	close_pipes(data, pipe_list, -1, -1);
	exec(data, i);
}

void	parent_process(t_data *data, t_pipe **pipe_list)
{
	close_pipes(data, pipe_list, -1, -1);
	while (waitpid(-1, NULL, 0) != -1)
	{
	}
	free_pipes(data->pipe_list);
}

size_t	count_pipes(t_command *command_list)
{
	size_t	n;
	size_t	i;

	n = 1;
	i = 0;
	while (command_list[i].command != NULL)
	{
		if (command_list[i].type == TYPE_PIPE)
			n++;
		i++;
	}
	return (n);
}
