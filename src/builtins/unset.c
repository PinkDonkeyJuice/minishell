/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pinkdonkeyjuice <pinkdonkeyjuice@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:25:47 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/15 01:50:10 by pinkdonkeyj      ###   ########.fr       */
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
			free(to_delete->content);
			free(to_delete);
		}
		i++;
		var_def = data->commands[i];
	}
}
