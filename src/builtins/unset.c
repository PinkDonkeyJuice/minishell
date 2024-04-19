/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:25:47 by gyvergni          #+#    #+#             */
/*   Updated: 2024/04/19 17:52:21 by gyvergni         ###   ########.fr       */
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
			previous = search_var_before(var_def, data);
			to_replace->content = var_def;
		}
		else
			append_node(&(data->env_c), var_def);
		i++;
	}
}