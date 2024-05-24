/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:25:47 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/24 16:18:20 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	env_len(t_env *env_c)
{
	size_t	len;
	t_env	*node;
	
	len = 0;
	node = env_c;
	while (node)
	{
		len++;
		node = node->next;
	}
	return (len);
}

void	exec_unset(t_data *data)
{
	int		i;
	char	*var_def;
	t_env	*to_delete;
	t_env	*prev_node;

	i = 1;
	var_def = data->commands[i];
	while (var_def != NULL)
	{
		to_delete = search_var(var_def, data);
		if (to_delete != NULL)
		{
			prev_node = to_delete->previous;
			prev_node->next = to_delete->next;
			if (to_delete->next != NULL)
				to_delete->next->previous = prev_node;
			if (env_len(data->env_c) == 1)
				data->env_c = NULL;
			free(to_delete->content);
			free(to_delete);
		}
		i++;
		var_def = data->commands[i];
	}
}
