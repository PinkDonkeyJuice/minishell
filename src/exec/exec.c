/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:26:03 by gyvergni          #+#    #+#             */
/*   Updated: 2024/04/19 14:39:30 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_commands(char **commands)
{
	size_t		i;

	i = 0;
	while (commands[i])
	{
		printf("Command read %zu is %s\n", i, commands[i]);
		i++;
	}
}

char **get_commands(t_command *command_list, size_t i)
{
	size_t i_pipe;
	size_t i_start;
	char **commands;
	size_t n;
	size_t	j;

	i_start = 0;
	i_pipe = 0;
	while (i_pipe != i)
	{
		if (command_list[i_start].type == TYPE_PIPE)
			i_pipe++;
		i_start++;
	}
	n = 0;
	j = 0;
	while (command_list[i_start + j].type != TYPE_PIPE && command_list[i_start + j].command != NULL)
	{
		if (command_list[i_start + j].type != TYPE_OPERATOR && \
			((i_start + j == 0) || command_list[i_start + j - 1].type != TYPE_OPERATOR))
			n++;
		j++;
	}
	commands = (char **)malloc(sizeof(char *) * (n + 1));
	//printf("n is: %zu\ni_start is: %zu\n", n, i_start);
	j = 0;
	while (j != n)
	{
		if (command_list[i_start + j].type != TYPE_OPERATOR && \
			((i_start + j == 0) || command_list[i_start + j - 1].type != TYPE_OPERATOR))
		{	
			commands[j] = ft_strdup(command_list[i_start + j].command);
			j++;
		}
		else
			i_start++;
	}
	commands[n] = NULL;
	return (commands);
}

void	exec(t_data *data, size_t i)
{
	char	*path;
	char	**commands;

	commands = get_commands(data->command_list, i);
	//read_commands(commands);
	data->commands = commands;
	if (check_builtins(data) == 0)
	{
		path = get_exec_path(commands[0]);
		if (!path)
		{
			printf("Unkown command\n");
			exit(-1) ;
		}
		if (data->fdin != STDIN_FILENO)
			close(data->fdin);
		execve(path, commands, data->env);
	}
	exit(1);
}

void	child_proc(t_data *data, t_pipe **pipe_list, size_t i)
{
		if (i == 0)
		{
			if (data->n_commands == 1)
			{
				dup2(data->fdin, STDIN_FILENO);
				dup2(data->fdout, STDOUT_FILENO);
				exec(data, i);
			}
			if (data->fdin != STDIN_FILENO)
				dup2(data->fdin, STDIN_FILENO);
			close(access_pipe(pipe_list, i)->p[0]);
			dup2(access_pipe(pipe_list, i)->p[1], STDOUT_FILENO);
			close(access_pipe(pipe_list, i)->p[1]); // Close write end of pipe after duplicating
		}
		else if (i == data->n_commands - 1)
		{
			if (data->fdout != STDOUT_FILENO)
				dup2(data->fdout, STDOUT_FILENO);
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

void	exec_commands(t_data *data)
{
	t_pipe	*pipe_list;
	
	handle_input_output(data);
	printf("fdin : %d, fdout: %d\n", data->fdin, data->fdout);
	pipe_list = NULL;
	generate_pipes(&pipe_list, data);
	redir(data, &pipe_list);
}
