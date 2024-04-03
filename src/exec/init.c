/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:23:08 by gyvergni          #+#    #+#             */
/*   Updated: 2024/04/03 12:57:19 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data)
{
	int	pip[2];

	if (pipe(pip) == -1)
	{
		perror("In main: ");
		return ;
	}
	data->fdout = -1;
	data->fdin = -1;
	data->pipin = pip[0];
	data->pipout = pip[1];
	return ;
}