#include "minishell.h"

void	exec_cd(t_data *data)
{
	t_env	*home;
	char	*path;

	home = NULL;
	path = NULL;
	if (data->n_commands > 1)
		return ;
	if (data->command_list[1].command != NULL)
	{
		if (data->command_list[2].command && data->command_list[2].command != NULL)
		{
			printf("minishell: cd: too many arguments\n");
			data->last_error = 127;
			return ;
		}
		chdir(data->command_list[1].command);
		if (errno == EACCES)
			return ((void) printf("minishell: cd: permission denied: %s\n", data->command_list[1].command));
		if (errno == ENOENT)
			return ((void) printf("minishell: cd: no such file or directory\n"));
	}
	else
	{
		home = search_var("HOME", data);
		//if (!home_path)
			/**/
		path = cont_of_var(home->content);
		/*if (!path)
			*/
		chdir(path);
	}
}
