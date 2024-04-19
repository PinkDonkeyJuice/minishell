
#include "minishell.h"

int	is_exit(char *line)
{
	int	i;
	int	j;
	char	*exit;

	i = 0;
	j = 0;
	exit = "exit";
	while (line[i])
	{
		j = 0;
		while (line[i + j] == exit[j])
		{
			if (line[i + j] == exit[j] && exit[j + 1] == '\0' 
				&& (line[i + j + 1] == ' ' || line[i + j + 1] == '\0'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	is_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	exit_atoi(const char *str)
{
	size_t			i;
	int				n;
	unsigned char	nb;
	int				sign;

	i = 0;
	n = 0;
	nb = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = (n * 10) + (str[i] - '0');
		i++;
	}
	nb = (unsigned char) n;
	if (sign == -1)
		return (256 - (int) nb);
	return ((int) nb);
}

void	do_exit(t_data *data)
{
	printf("exit\n");
	exit(data->last_error);
}

void	exec_exit(t_data *data)
{
	if (data->n_commands > 1)
		return ;
	if (!data->command_list[1].command)
		do_exit(data);
	else
	{
		if (data->command_list[1].command != NULL && is_num(data->command_list[1].command))
		{
			if (data->command_list[2].command != NULL)
			{
				printf("exit\nminishell: exit: too many arguments\n");
				data->last_error = 1;
				return ;
			}
			printf("exit\n");
			exit(exit_atoi(data->command_list[1].command));
		}
		else
		{
			printf("exit\nminishell: exit: %s: numeric argument required\n",
				data->command_list[1].command);
			exit(2);
		}
	}
}
