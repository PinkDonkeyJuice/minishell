/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:26:03 by gyvergni          #+#    #+#             */
/*   Updated: 2024/04/15 13:09:56 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **next_command(t_command *command_list, size_t i)
{
	size_t ind;
	size_t j;
	char **commands;
	size_t n;

	j = 0;
	ind = 0;
	while(ind != i)
	{
		if (command_list[i + j].type == TYPE_COMMAND || command_list[i + j].type == TYPE_OPTION)
			ind++;
		j++;
	}
	n = 1;
	while(command_list[i + j + n - 1].command != TYPE_PIPE)
		n++;
	commands = malloc(sizeof(char *) * (n + 1));
	while()
	commands[0] = ft_strdup(command_list[i + j + 1])
}

void	exec(t_data *data, size_t i)
{
	char **cmd_split;
	char	*path;

	cmd_split = ft_split(next_command(data->command_list, i), ' ');
	path = get_exec_path(data->command_list);
	if (!path)
		return ;
	execve(path, cmd_split, data->env);
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



	void	exec_commands(t_data *data)
	{
		t_pipe	*pipe_list;

		data->n_commands = commands_len(commands);
		pipe_list = NULL;
		generate_pipes(&pipe_list, data);
		redir(data, &pipe_list);
	}