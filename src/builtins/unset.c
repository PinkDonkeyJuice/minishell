/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pinkdonkeyjuice <pinkdonkeyjuice@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:25:47 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/29 16:20:00 by pinkdonkeyj      ###   ########.fr       */
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

void	free_to_delete(t_env *to_delete)
{
	free(to_delete->content);
	free(to_delete);
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
		if (to_delete != NULL && to_delete->modifiable == true)
		{
			prev_node = to_delete->previous;
			if (prev_node != NULL)
				prev_node->next = to_delete->next;
			if (to_delete->next != NULL)
				to_delete->next->previous = prev_node;
			printf("env size = %zu\n", env_len(data->env_c));
			if (prev_node == NULL)
				data->env_c = to_delete->next;
			free_to_delete(to_delete);
		}
		i++;
		var_def = data->commands[i];
	}
}
