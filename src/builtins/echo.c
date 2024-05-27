/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:38:43 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/27 12:56:29 by gyvergni         ###   ########.fr       */
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
		return ;
	newl = true;
	while (data->commands[i] && is_dash_n(data->commands[i]))
	{
		newl = false;
		i++;
	}
	while (data->commands[i])
	{
		printf("%s", data->commands[i]);
		if (data->commands[i + 1] && data->commands[i + 1][0] != '\0'
			&& data->commands[i][0] != '\0')
			printf(" ");
		i++;
	}
	if (newl == true)
		printf("\n");
}
