/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:25:47 by gyvergni          #+#    #+#             */
/*   Updated: 2024/04/22 14:18:02 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_unset(t_data *data)
{
	int		i;
	char	*var_def;
	t_env	*to_delete;
	t_env	*prev_node;

	i = 1;
	while ((var_def = data->commands[i]) != NULL)
	{
		if ((to_delete = search_var(var_def, data)) != NULL)
		{
			prev_node = to_delete->previous;
			prev_node->next = to_delete->next;
			if (to_delete->next != NULL)
				to_delete->next->previous = prev_node;
			free(to_delete);
		}
		i++;
	}
}