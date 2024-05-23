/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:23:08 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/23 13:46:11 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data)
{
	data->fdout = STDOUT_FILENO;
	data->fdin = STDIN_FILENO;
	data->heredoc_name = NULL;
	data->delimiter = NULL;
	data->pipe_list = NULL;
	data->env_c = NULL;
	data->commands = NULL;
	data->command_list = NULL;
	data->i_command = 0;
	data->last_error = 0;
	data->pipe_list = NULL;
	return ;
}
