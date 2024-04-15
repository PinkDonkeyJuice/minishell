/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:26:03 by gyvergni          #+#    #+#             */
/*   Updated: 2024/04/15 14:15:30 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **get_commands(t_command *command_list, size_t i)
{
	size_t ind;
	size_t j;
	char **commands;
	size_t n;

	j = 0;
	ind = 0;
	while (ind != i)
	{
		if (command_list[j].type == TYPE_PIPE)
			ind++;
		j++;
	}
	n = 0;
	while (command_list[j + n].type != TYPE_PIPE)
		n++;
	commands = malloc(sizeof(char *) * (n + 1));
	ind = 0;
	while (ind != n)
	{
		if (command_list[j + ind].type != TYPE_OPERATOR && command_list[j + ind - 1].type != TYPE_OPERATOR)
			commands[n] = ft_strdup(command_list[j + ind].command);
		ind++;
	}
	return (commands);
}

void	exec(t_data *data, size_t i)
{
	char **commands;
	char	*path;

	commands = get_commands(data->command_list, i);
	path = get_exec_path(commands[0]);
	if (!path)
		return ;
	execve(path, commands, data->env);
}

void	child_proc(t_data *data, t_pipe **pipe_list, size_t i)
{
		if (i == 0)
		{
			if (data->n_commands == 1)
				exec(data, i);
			close(access_pipe(pipe_list, i)->p[0]);
			dup2(access_pipe(pipe_list, i)->p[1], STDOUT_FILENO);
			close(access_pipe(pipe_list, i)->p[1]); // Close write end of pipe after duplicating
		}
		else if (i == data->n_commands - 1)
		{
			dup2(access_pipe(pipe_list, i - 1)->p[0], STDIN_FILENO);
			close(access_pipe(pipe_list, i - 1)->p[1]);
		}
		else
		{
			close(access_pipe(pipe_list, i - 1)->p[1]);
			dup2(access_pipe(pipe_list, i - 1)->p[0], STDIN_FILENO);
			close(access_pipe(pipe_list, i)->p[0]);
			dup2(access_pipe(pipe_list, i)->p[1], STDOUT_FILENO);
			close(access_pipe(pipe_list, i)->p[1]); // Close write end of pipe after duplicating
		}
		exec(data, i);
}

void	redir(t_data *data, t_pipe **pipe_list)
	{
		pid_t	parent;
		size_t	i;
	 
		i = 0;
		parent = 1;
		while (i < data->n_commands && parent)
		{
			if (parent)
				parent = fork();
			if (parent)
				i++;
			if (parent < 0)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
		}
		if (parent == 0)
		{
			waitpid(parent, NULL, 0);
			child_proc(data, pipe_list, i);
		}
		if (parent > 0)
		{
			close_all_pipes(data, pipe_list, -1, -1);
			while (waitpid(-1, NULL, 0) != -1)
			{
			}
		}
	}

size_t	count_pipes(t_command *command_list)
{
	size_t n;
	size_t i;

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

void	handle_input_output(t_data *data)
{
	size_t i;

	i = 0;
	while (data->command_list[i].command)
	{
		if (data->command_list[i].type == TYPE_OPERATOR)
		{
			//if (data->command_list[i].command == ft_strcmp(">"));
			{
				
			}
		}
	}
}

void	exec_commands(t_data *data)
{
	t_pipe	*pipe_list;
	
	data->n_commands = count_pipes(data -> command_list);
	pipe_list = NULL;
	generate_pipes(&pipe_list, data);
	redir(data, &pipe_list);
}