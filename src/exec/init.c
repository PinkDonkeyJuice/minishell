/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:23:08 by gyvergni          #+#    #+#             */
/*   Updated: 2024/04/30 15:33:13 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data)
{
	data->fdout = STDOUT_FILENO;
	data->fdin = STDIN_FILENO;
	data->heredoc_name = NULL;
	data->delimiter = NULL;
	return ;
}