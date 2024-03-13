/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pinkdonkeyjuice <pinkdonkeyjuice@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:45:20 by gyvergni          #+#    #+#             */
/*   Updated: 2024/03/13 12:38:36 by pinkdonkeyj      ###   ########.fr       */
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

void	exec(int *pip, char *path, char *line, char **env)
{
	char **cmd_split;

	cmd_split = ft_split(line, ' ');
	execve(path, cmd_split, env);
}

void	exec_commands(char *line, char **env)
{
	char	**commands;
	char	*path;
	int		parent;
	size_t	i;
	int		pip[2];

	commands = ft_split(line, '|');
	if (pipe(pip) == -1)
	{
	    perror("Error creating the pipe");
	    return ;
	}
	i = 0;
	while (commands[i])
	{
		if (!check_builtin(commands[i]))
		{
			path = get_exec_path(line);
			parent = fork();
			if (parent == 0)
				exec(pip, path, line, env);
			if (parent > 0)
			waitpid(-1, NULL, 0);
		}
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	char 	*line;
	t_mini	data;

	init_mini(data);
	while ((line = readline("$>")) != NULL)
	{
		//check_builtin(line);
		exec_commands(line, env);
	}
	return (0);
}