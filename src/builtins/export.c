/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:46:31 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/16 11:35:19 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_data *data)
{
	t_env	*print;

	print = data->env_c;
	while (print)
	{
		printf("declare -x ");
		printf("%s\n", print->content);
		print = print->next;
	}
	if (data->n_commands > 1)
	{
		free_commands(data->commands);
		free_command_list(data->command_list);
	}
}

void	exec_export(t_data *data)
{
	int		i;
	char	*var_def;
	t_env	*to_replace;	

	i = 1;
	if (data->commands == NULL || data->commands[0] == NULL)
		return ;
	if (!data->commands[1])
	{
		print_export(data);
		return ;
	}
	var_def = data->commands[i];
	while (var_def != NULL && data->n_commands == 1)
	{
		to_replace = search_var(var_def, data);
		printf("%s\n", to_replace->content);
		printf("%s\n", var_def);
		if (to_replace != NULL)
			to_replace->content = var_def;
		else
			append_node(&(data->env_c), var_def);
		i++;
		var_def = data->commands[i];
	}
}
