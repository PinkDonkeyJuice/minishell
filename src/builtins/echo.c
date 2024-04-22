#include "minishell.h"

void	exec_echo(t_data *data)
{
	int		i;
	bool	newl;

	i = 1;
	if (!data->commands[1])
		return ;
	newl = true;
	if (!ft_strcmp(data->commands[1], "-n"))
	{
		newl = false;
		i++;
	}
	while (data->commands[i])
	{
		printf("%s", data->commands[i]);
		if (data->commands[i + 1])
			printf(" ");
		i++;
	}
	if (newl == true)
		printf("\n");
}
