/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pinkdonkeyjuice <pinkdonkeyjuice@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:45:20 by gyvergni          #+#    #+#             */
/*   Updated: 2024/03/19 13:17:07 by pinkdonkeyj      ###   ########.fr       */
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