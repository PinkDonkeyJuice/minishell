/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:38:59 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/27 14:06:07 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_assigned(char *content)
{
	size_t	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

void	exec_env(t_data *data)
{
	t_env	*print;

	if (data->commands[1] != NULL)
	{
		data->last_error = 1;
		printf("Error: too many arguments to function call\n");
		return ;
	}
	print = data->env_c;
	while (print)
	{
		if (is_assigned(print->content))
			printf("%s\n", print->content);
		print = print->next;
	}
}
