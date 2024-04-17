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
			&& (line[i + 1] == '\0')/* && type != TYPE_OPERATOR*/)
			return (1);
		i++;
	}
	return (0);
}

void	exec_echo(t_data *data)
{
	int	i;

	i = 1;
	if (!data->commands[1])
		return ;
	while (data->commands[i])
	{
		//if (commande[i].type == TYPE_OPERATOR)
		//	(void) i;
		//else
		//{
			printf("%s", data->commands[i]);
			if (data->commands[i + 1] /*&& commande[i + 1].type != TYPE_OPERATOR)
				&& commande[i].type != TYPE_OPERATOR*/)
				printf(" ");
		//}
		i++;
	}
	printf("\n");
}
