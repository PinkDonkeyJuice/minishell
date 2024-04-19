/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:23:08 by gyvergni          #+#    #+#             */
/*   Updated: 2024/04/19 15:14:45 by gyvergni         ###   ########.fr       */
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
	data->fdout = STDOUT_FILENO;
	data->fdin = STDIN_FILENO;
	data->heredoc_name = NULL;
	data->pipin = pip[0];
	data->pipout = pip[1];
	data->delimiter = NULL;
	return ;
}