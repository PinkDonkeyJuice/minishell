/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:55:09 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/06 12:24:33 by gyvergni         ###   ########.fr       */
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
	free_all(data);
	ft_putstr_fd(err_msg, 2);
	exit(errno);	
}
