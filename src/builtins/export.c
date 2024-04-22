/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:46:31 by nchaize-          #+#    #+#             */
/*   Updated: 2024/04/22 15:49:07 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_export(t_data *data)
{
	int		i;
	char	*var_def;
	t_env	*to_replace;	

	i = 1;
	if (!data->commands[1])
		exec_env(data);
	while ((var_def = data->commands[i]) != NULL && data->n_commands == 1)
	{
		if ((to_replace = search_var(var_def, data)) != NULL)
			to_replace->content = var_def;
		else
			append_node(&(data->env_c), var_def);
		i++;
	}
}
