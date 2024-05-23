/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:36:45 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/23 14:03:54 by gyvergni         ###   ########.fr       */
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
	{
		free(oldpwd->content);
		oldpwd->content = var_oldpwd;
	}
}

void	update_pwd(t_data *data)
{
	char	buf[PATH_MAX];
	t_env	*pwd;
	char	*var_pwd;

	if (getcwd(buf, PATH_MAX))
		var_pwd = ft_strjoin("PWD=", buf);
	else 
		var_pwd = NULL;
	pwd = search_var("PWD", data);
	if (pwd)
	{
		free(pwd->content);
		pwd->content = var_pwd;
	}
}

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

void	exec_cd(t_data *data)
{
	char	*path;
	t_env	*var_old;

	path = NULL;
	if (data->n_commands > 1)
		return ;
	if (data->commands[1] && data->commands[2] != NULL)
		return (data->last_error = 1,
			(void) printf("Error: too many arguments to function call\n"));
	else if (data->commands[1] != NULL)
		path = get_path_cd(data, path);
	else if (data->commands[1] == NULL)
		path = get_path_cd_options(data, path);
	printf("Path is : %s\n", path);
	if (!path)
		return ;
	if (access(path, F_OK) == -1)
		return (data->last_error = 2,
			(void) printf("minishell: cd: no such file or directory\n"));
	if (access(path, R_OK) == -1)
		return (data->last_error = 1,
			(void) printf("minishell: cd: permission denied\n"));
	var_old = search_var("PWD", data);
	if (var_old == NULL)
	{
		printf("Unable to access directory\n");
		return ;
	}
	update_oldpwd(data, cont_of_var(var_old->content));
	if (path)
		chdir(path);
	update_pwd(data);
}
