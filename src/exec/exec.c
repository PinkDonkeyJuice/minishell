/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:26:03 by gyvergni          #+#    #+#             */
/*   Updated: 2024/04/03 14:36:15 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_data *data, size_t i)
{
	char **cmd_split;
	char	*path;
	
	cmd_split = ft_split(data->commands[i], ' ');
	path = get_exec_path(data->commands[i]);
	if (!path)
		return ;
	execve(path, cmd_split, data->env);
}

void	child_proc(t_data *data, t_pipe **pipe_list, size_t i)
{
	if (i == 0)
	{
		if (data->fdin != -1)
			dup2(data->fdin, STDIN_FILENO);
		if (data->n_commands == 1)
			exec(data, i);
		dup2(access_pipe(pipe_list, i)->p[1], STDOUT_FILENO);
		close(access_pipe(pipe_list, i)->p[0]);
	}
	else if (i == data->n_commands - 1)
	{
		dup2(access_pipe(pipe_list, i - 1)->p[0], STDIN_FILENO);
		close(access_pipe(pipe_list, i - 1)->p[1]);
		if (data->fdout != -1)
			dup2(data->fdout, 1);
	}
	else
	{
		close(access_pipe(pipe_list, i - 1)->p[1]);
		dup2(access_pipe(pipe_list, i - 1)->p[0], STDIN_FILENO);
		dup2(access_pipe(pipe_list, i)->p[0], STDOUT_FILENO);
		close(access_pipe(pipe_list, i)->p[1]);
	}
	//close_all_pipes(data, pipe_list, i);
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
	}
	if (parent < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (parent == 0)
		child_proc(data, pipe_list, i);
	else if (parent > 0)
	{
		close_all_pipes(data, pipe_list, -1);
		waitpid(parent, NULL, 0);
	}
}

void	exec_commands(t_data *data)
{
	char	**commands;
	t_pipe	*pipe_list;

	commands = ft_split(data->line, '|');
	data->commands = commands;
	data->n_commands = commands_len(commands);
	pipe_list = NULL;
	generate_pipes(&pipe_list, data);
	//data->fdin = open("input.txt", O_RDWR | O_APPEND , 0644);
	//data->fdout = open("output.txt", O_RDWR | O_APPEND | O_CREAT, 0644);
	redir(data, &pipe_list);
}
