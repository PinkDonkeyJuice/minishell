/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:38:43 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/02 14:18:06 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	free_all(data);
}
