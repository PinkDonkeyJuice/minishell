/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:23:08 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/13 14:17:24 by nchaize-         ###   ########.fr       */
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
	return ;
}
