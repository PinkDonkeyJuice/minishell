/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:36:45 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/27 15:43:47 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_oldpwd(t_data *data, char *path_oldpwd)
{
	t_env	*oldpwd;
	char	*var_oldpwd;

	oldpwd = NULL;
	var_oldpwd = NULL;
	if (path_oldpwd != NULL)
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

	getcwd(buf, PATH_MAX);
	var_pwd = ft_strjoin("PWD=", buf);
	pwd = search_var("PWD", data);
	if (pwd)
	{
		free(pwd->content);
		pwd->content = var_pwd;
	}
}

void	exec_cd(t_data *data)
{
	char	*path;
	t_env	*var_old;
	char	*var_old_content;

	path = NULL;
	path = make_path(data, path);
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
		var_old_content = NULL;
		printf("Unable to access directory\n");
	}
	else
		var_old_content = var_old->content; 
	update_oldpwd(data, cont_of_var(var_old_content));
	if (path)
		chdir(path);
	update_pwd(data);
}
