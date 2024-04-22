/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pinkdonkeyjuice <pinkdonkeyjuice@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:25:47 by gyvergni          #+#    #+#             */
/*   Updated: 2024/04/22 11:21:05 by pinkdonkeyj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_unset(t_data *data)
{
	int		i;
	char	*var_def;
	t_env	*to_delete;
	t_env	*previous;

	i = 0;
	while ((var_def = data->commands[i + 1]) != NULL)
	{
		if ((to_delete = search_var(var_def, data)) != NULL)
		{	
			previous = to_delete->previous;
			previous->next = to_delete->next;
			to_delete->next->previous = previous;
			free(to_delete);
		}
		else
			append_node(&(data->env_c), var_def);
		i++;
	}
}
