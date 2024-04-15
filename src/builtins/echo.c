#include "minishell.h"

int	is_echo(char *line)
{
	int	i;
	char	*echo;

	i = 0;
	echo = "echo";
	while (line[i] == echo[i])
	{
		if (line[i] == echo[i] && echo[i + 1] == '\0' 
			&& (line[i + 1] == '\0' || is_operator(&line[i])))
			return (1);
		i++;
	}
	return (0);
}


void	exec_echo(t_data *data)
{
	int	i;

	i = 1;
	if (!data->command_list[1].command)
		return ;
	//if (is_operator(data->command[i]))
	//	return ;
	while (data->command_list[i].command != NULL)
	{
		//if (is_operator(data->command[i]))
		//	(void) i;
		//else
		//{
			printf("%s", data->command_list[i].command);
			if (data->command_list[i + 1].command /*&& !is_operator(data->command[i + 1])
				&& !is_operator(data->command[i])*/)
				printf(" ");
		//}
		i++;
	}
	printf("\n");
}