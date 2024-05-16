/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:38:43 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/16 11:05:43 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dash_n(char *command)
{
	int		i;
	char	*option;

	i = 0;
	option = "-n";
	while (command[i] == option[i])
	{
		if (!option[i + 1] && command[i + 1])
		{
			while (command[i] && command[i] == 'n')
			{
				if (!command[i + 1] && command[i] == 'n')
					return (1);
				i++;
			}
		}
		if (!option[i + 1] && !command[i + 1])
			return (1);
		i++;
	}
	return (0);
}

void	exec_echo(t_data *data)
{
	int		i;
	bool	newl;

	i = 1;
	if (!data->commands[1])
	{
		free_all(data);
		return ;
	}
	newl = true;
	if (data->commands[1] && is_dash_n(data->commands[1]))
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
	free_all_comms(data);
}
