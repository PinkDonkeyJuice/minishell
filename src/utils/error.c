/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:55:09 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/06 15:31:14 by nchaize-         ###   ########.fr       */
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
