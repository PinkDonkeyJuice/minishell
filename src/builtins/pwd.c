/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:42:26 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/16 11:09:09 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pwd(t_data *data)
{
	char	buf[PATH_MAX];

	if (getcwd(buf, PATH_MAX))
		printf("%s\n", buf);
	else
		perror("Pwd: ");
	free_all_comms(data);
}
