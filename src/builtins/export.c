/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:46:31 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/03 11:45:11 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_export(t_data *data)
{
	int		i;
	char	*var_def;
	t_env	*to_replace;	

	i = 1;
	if (data->commands == NULL)
		return ;
	if (!data->commands[1])
		exec_env(data);
	var_def = data->commands[i];
	while (var_def != NULL && data->n_commands == 1)
	{
		to_replace = search_var(var_def, data);
		if (to_replace != NULL)
			to_replace->content = var_def;
		else
			append_node(&(data->env_c), var_def);
		i++;
		var_def = data->commands[i];
	}
}
