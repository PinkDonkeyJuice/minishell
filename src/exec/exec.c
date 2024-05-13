/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:26:03 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/13 14:26:45 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_no_commands(void)
{
	printf("Memory allocation problem encountered during get_commands_\n");
	exit(-1);
}

void	exec_utils(t_data *data)
{
	//changer le nom de la fonction pour mieux correspondre a son utilité
	close_safe(data,
		access_pipe(data->pipe_list, data->n_commands - 1)->p[0]);
	write(access_pipe(data->pipe_list, data->n_commands - 1)->p[1],
		&(data->last_error), 1);
	close_safe(data,
		access_pipe(data->pipe_list, data->n_commands - 1)->p[1]);
}

void	exec(t_data *data, size_t i)
{
	char	*path;

	free_commands(data->commands);
	data->commands = get_commands(data->command_list, i);
	if (data->commands == NULL)
		do_no_commands();
	data->i_command = i;
	if (check_builtins(data) == 0)
	{
		data->last_error = 0;
		path = get_exec_path(data->commands[0], data);
		if (!path)
			error(data, NULL);
		if (data->fdin != STDIN_FILENO)
			close_safe(data, data->fdin);
		if (i == data->n_commands - 1)
			exec_utils(data);
		execve(path, data->commands, data->env);
	}
	if (data->env_c)
		free_env(data->env_c);
	free_pipes(data->pipe_list);
	exit(1);
}

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
	if (i != data->n_commands - 1)
		close_pipes(data, pipe_list, -1, -1);
	else
		close_pipes(data, pipe_list, data->n_commands - 1, -1);
	exec(data, i);
}

void	mark_status(int status, t_data *data)
{
	int	term_sig;

/* 	if (WIFEXITED(status))
	{
		write(1, "c\n", 2);
		data->last_error = WEXITSTATUS(status);
	} */
	if (WIFSIGNALED(status))
	{
		term_sig = WTERMSIG(status);
		if (term_sig == SIGQUIT)
		{
			data->last_error = 131;
		}
		else if (term_sig == SIGINT)
		{
			data->last_error = 130;
		}
	}
}

void	parent_process(t_data *data, t_pipe **pipe_list)
{
	int	status;
	int	pid;
	int	last_error;

	while (waitpid(-1, &status, 0) != -1)
	{
		mark_status(status, data);
	}
	close_safe(data, access_pipe(pipe_list, data->n_commands - 1)->p[1]);
	if (read((access_pipe(pipe_list, data->n_commands - 1)->p[0]),
			&(last_error), sizeof(int)) == -1)
		return ;
	close_safe(data, access_pipe(pipe_list, data->n_commands - 1)->p[0]);
	data->last_error = (int)last_error;
	printf("Last error = %d\nData->last_error = %d\n",
		last_error, data->last_error);
	close_pipes(data, pipe_list, data->n_commands - 1, -1);
	free_pipes(data->pipe_list);
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
			n++;
		i++;
	}
	return (n);
}
