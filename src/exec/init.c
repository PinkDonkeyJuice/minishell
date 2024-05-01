/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pinkdonkeyjuice <pinkdonkeyjuice@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:23:08 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/01 18:30:35 by pinkdonkeyj      ###   ########.fr       */
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
	return ;
}