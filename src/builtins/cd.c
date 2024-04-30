/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:36:45 by gyvergni          #+#    #+#             */
/*   Updated: 2024/04/30 14:37:36 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_oldpwd(t_data *data, char *path_oldpwd)
{
	t_env	*oldpwd;
	char	*var_oldpwd;

	var_oldpwd = ft_strjoin("OLDPWD=", path_oldpwd);
	oldpwd = search_var("OLDPWD", data);
	if (oldpwd != NULL)
		oldpwd->content = var_oldpwd;
}

void	update_pwd(t_data *data)
{
	char	buf[PATH_MAX];
	t_env	*pwd;
	char	*var_pwd;

	if (getcwd(buf, PATH_MAX))
		var_pwd = ft_strjoin("PWD=", buf);
	pwd = search_var("PWD", data);
	if (pwd)
		pwd->content = var_pwd;
}

char	*get_path_cd_options(t_data *data, char *path)
{
	t_env	*target;

	target = NULL;
	if (data->commands[1] != NULL && !ft_strcmp(data->commands[1], "-"))
	{
		target = search_var("OLDPWD", data);
		if (!target)
			return (NULL);
		path = cont_of_var(target->content);
		printf("Path is: %s\n", path);
	}
	else if (data->commands[1] == NULL)
	{
		target = search_var("HOME", data);
		if (!target)
			return (NULL);
		path = cont_of_var(target->content);
		printf("Path is: %s\n", path);
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

void	exec_cd(t_data *data)
{
	char	*path;

	path = NULL;
	if (data->n_commands > 1)
		return ;
	else if (data->commands[1] != NULL && \
		ft_strcmp(data->commands[1], "-") != 0)
		path = get_path_cd(data, path);
	else
		path = get_path_cd_options(data, path);
	if (!path)
		return ;
	update_oldpwd(data, cont_of_var(search_var("PWD", data)->content));
	chdir(path);
	update_pwd(data);
}
