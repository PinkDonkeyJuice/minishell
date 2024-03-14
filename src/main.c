/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:45:20 by gyvergni          #+#    #+#             */
/*   Updated: 2024/03/14 16:13:35 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "stdlib.h"
#include "minishell.h"

char	*get_exec_path(char *line)
{
	int		i;
	char 	**paths;
	char	*try_path;
	char 	**cmd_split;

	paths = ft_split(getenv("PATH"), ':');
	cmd_split = ft_split(line, ' ');
	i = 0;
	if (paths && cmd_split)
	{
		while (paths[i])
		{
			if ((try_path = ft_strdup(paths[i])) == NULL)
				return (NULL);
			if ((try_path = ft_strjoin(try_path, "/")) == NULL)
				return (NULL);
			if ((try_path = ft_strjoin(try_path, cmd_split[0])) == NULL)
				return (NULL);
			if (access(try_path, X_OK) == 0)
				return (try_path);
			i++;
		}
	}
	return (NULL);
}

int	check_builtin(char *command)
{
	char *nul;

	nul = command;
	nul++;
	return (0);
}

size_t	commands_len(char **commands)
{
	size_t i;

	i = 0;
	while (commands[i])
		i++;
	return (i);
}

void	exec(t_data *data, size_t i)
{
	char **cmd_split;
	char	*path;
	
	cmd_split = ft_split(data->commands[i], ' ');
	path = get_exec_path(data->commands[i]);
/* 	if (!path)
		return ; */
	//printf("There are %ld commands\nWe are on command %ld, Pipin is %d\nPipout is %d\n", data->n_commands, i, data->pipin, data->pipout);
	execve(path, cmd_split, data->env);
}

void	redir(t_data *data, size_t i)
{
	pid_t	parent;

	parent = fork();
	if (parent == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (parent == 0)
	{
		dup2(data->pipout, 1);
		close(data->pipin); // Close the read end of the pipe
		exec(data, i); // Execute the command
		exit(EXIT_FAILURE); // Exit child process after execution
	}
	else
	{
		dup2(data->pipin, 0);
		close(data->pipout); // Close the read end of the pipe
		waitpid(-1, NULL, 0); // Wait for child process to finish
	}
}

void	exec_commands(t_data *data)
{
	char	**commands;
	size_t	i;
	pid_t	parent;
	
	commands = ft_split(data->line, '|');
	data->commands = commands;
	data->n_commands = commands_len(commands);
	i = 0;
	while (i < data->n_commands - 1)
	{
		if (!check_builtin(commands[i]))
			redir(data, i);
		i++;
	}
	parent = fork();
	if (!parent)
		exec(data, i);
	if (parent)
		waitpid(-1, NULL, 0);
}

int	main(int argc, char **argv, char **env)
{
	char 	*line;
	t_data	data;

	(void)argv;
	(void)argc;
	init_data(&data);
	data.env = env;
	while ((line = readline("$>")) != NULL)
	{
		//check_builtin(line);
		data.line = line;
		exec_commands(&data);
	}
	return (0);
}