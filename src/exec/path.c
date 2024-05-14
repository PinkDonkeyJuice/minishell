/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:16:53 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/14 17:16:53 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_path(char *command, char *path)
{
	char *try_path;

	try_path = NULL;
	try_path = ft_strdup(path);
	if (try_path != NULL)
		try_path = ft_strjoin(try_path, "/");
	if (try_path != NULL)
		try_path = ft_strjoin(try_path, command);
	return (try_path);
}

char *get_exec_path_return(t_data *data, char *command)
{
	if (!ft_strncmp("./", command, 2))
	{
		if (access(command, X_OK) != 0)
			data->last_error = 127;
		return (command);
	}
	printf("Command not found: %s\n", command);
	data->last_error = 127;
	return (NULL);
}

char	*get_exec_path(char *command, t_data *data)
{
	int		i;
	char	**paths;
	char	*try_path;

	paths = ft_split(getenv("PATH"), ':');
	if (!paths)
		return (data->last_error = 1, NULL);
	try_path = NULL;
	i = 0;
	if (paths && command)
	{
		while (paths[i])
		{
			try_path = create_path(command, paths[i]);
			if (!try_path)
				return (NULL);
			if (access(try_path, X_OK) == 0)
				return (try_path);
			i++;
			free(try_path);
		}
	}
	return (get_exec_path_return(data, command));
}
