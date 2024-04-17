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
	if (data->command_list[2].command != NULL)
	{
		printf("minishell: cd: too many arguments\n");
		data->last_error = 127;
		return ;
	}
	if (data->command_list[1].command)
	{
		//if (/*pas possible d'ouvrir*/)
			/*message d'erreur*/
		chdir(data->command_list[1].command);
	}
	else
	{
		//go home
	}
}
