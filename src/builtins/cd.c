#include "minishell.h"

void	update_oldpwd(t_data *data, char *path_oldpwd, char *path_pwd)
{
	t_env	*oldpwd;
	t_env	*pwd;
	char	*var_oldpwd;
	char	*var_pwd;

	var_oldpwd = ft_strjoin("OLDPWD=", path_oldpwd);
	oldpwd = search_var("OLDPWD", data);
	if (oldpwd != NULL)
		oldpwd->content = var_oldpwd;
	var_pwd = ft_strjoin("PWD=", path_pwd);
	pwd = search_var("PWD", data);
	if (pwd != NULL)
		pwd->content = var_pwd;
	printf("Old pwd: %s\n", pwd->content);
}

void	exec_cd(t_data *data)
{
	t_env	*target;
	char	*path;

	target = NULL;
	path = NULL;
	if (data->n_commands > 1)
		return ;
	if (data->commands[1] != NULL && !ft_strcmp(data->commands[1], "-"))
	{
		target = search_var("OLDPWD", data);
		if (!target)
			return ;
		path = cont_of_var(target->content);
		printf("Path is: %s\n", path);
		if (!path)
			return ;
	}
	else if (data->commands[1] != NULL)
	{
		if (data->commands[2])
		{
			printf("minishell: cd: too many arguments\n");
			data->last_error = 127;
			return ;
		}
		printf("Path is: %s\n", data->commands[1]);
		path = data->commands[1];
		if (errno == EACCES)
			return ((void) printf("minishell: cd: permission denied: %s\n", data->commands[1]));
		if (errno == ENOENT)
			return ((void) printf("minishell: cd: no such file or directory\n"));
	}
	else
	{
		target = search_var("HOME", data);
		if (!target)
			return ;
		path = cont_of_var(target->content);
		printf("Path is: %s\n", path);
		if (!path)
			return ;
	}
	update_oldpwd(data, cont_of_var(search_var("PWD", data)->content), path);
	chdir(path);
}
