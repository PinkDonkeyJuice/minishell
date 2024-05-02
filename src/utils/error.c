/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:55:09 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/02 12:59:19 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_safe( t_data *data, int fd)
{
	if (close(fd) == -1)
	{
		free_all(data);
		perror("Closing file: ");
		exit(-1);
	}

}

void	error(t_data *data, char *err_msg)
{
	free(data->line);
	free_commands(data->commands);
	free_env(data->env_c);
	free_pipes(data->pipe_list);
	ft_putstr_fd(err_msg, 2);	
}
