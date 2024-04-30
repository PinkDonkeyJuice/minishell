/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:42:26 by gyvergni          #+#    #+#             */
/*   Updated: 2024/04/30 14:42:27 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pwd(void)
{
	char	buf[PATH_MAX];

	if (getcwd(buf, PATH_MAX))
		printf("%s\n", buf);
	else
		perror("Pwd: ");
}
