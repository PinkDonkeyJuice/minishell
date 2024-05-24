/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:15:55 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/24 11:26:51 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_cd_options(t_data *data, char *path)
{
	t_env	*target;

	target = NULL;
	if (data->commands[1] == NULL)
	{
		target = search_var("HOME", data);
		if (!target)
			return (NULL);
		path = cont_of_var(target->content);
	}
	return (path);
}

char	*get_path_cd(t_data *data, char *path)
{
	if (data->commands[2])
	{
		printf("minishell: cd: too many arguments\n");
		data->last_error = 127;
		return (NULL);
	}
	path = data->commands[1];
	if (errno == EACCES)
		return (printf("minishell: cd: permission denied: %s\n", \
			data->commands[1]), path);
	if (errno == ENOENT)
		return (printf("minishell: cd: no such file or directory\n"), path);
	return (path);
}

char	*make_path(t_data *data, char *path)
{
	if (data->n_commands > 1)
		path = NULL;
	else if (data->commands[1] && data->commands[2] != NULL)
	{
		data->last_error = 1;
		printf("Error: too many arguments to function call\n");
		path = NULL;
	}
	else if (data->commands[1] != NULL)
		path = get_path_cd(data, path);
	else if (data->commands[1] == NULL)
		path = get_path_cd_options(data, path);
	return (path);
}
