/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:38:59 by gyvergni          #+#    #+#             */
/*   Updated: 2024/04/30 14:39:20 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_env(t_data *data)
{
	t_env	*print;

	print = data->env_c;
	while (print)
	{
		printf("%s\n", print->content);
		print = print->next;
	}
}
