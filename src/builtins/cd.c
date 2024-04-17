#include "minishell.h"

int	is_cd(char *line)
{
	int	i;
	int	j;
	char	*cd;

	i = 0;
	j = 0;
	cd = "cd";
	while (line[i])
	{
		j = 0;
		while (line[i + j] == cd[j])
		{
			if (line[i + j] == cd[j] && cd[j + 1] == '\0' 
				&& (line[i + j + 1] == ' ' || line[i + j + 1] == '\0'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	exec_cd(t_data *data)
{
	t_env	*home_path;
	char	*path;

	home_path = NULL;
	path = NULL;
	if (data->n_commands > 1)
		return ;
	if (data->command_list[2].command)
	{
		printf("minishell: cd: too many arguments\n");
		data->last_error = 127;
		return ;
	}
	if (data->command_list[1].command)
	{
		chdir(data->command_list[1].command);
		if (errno == EACCES)
			return ((void) printf("minishell: cd: permission denied: %s\n", data->command_list[1].command));
		//if (errno == ENOENT)
			//return ((void) printf("minishell: cd: no such file or directory\n"));
	}
	else
	{
		home_path = search_var("HOME", data);
		//if (!home_path)
			/**/
		path = cont_of_var(home_path->content);
		/*if (!path)
			*/
		chdir(path);
	}
}
