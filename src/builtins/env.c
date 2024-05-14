/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pinkdonkeyjuice <pinkdonkeyjuice@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:38:59 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/05 20:01:31 by pinkdonkeyj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_env(t_data *data)
{
	t_env	*print;

	if (data->commands[1] != NULL)
	{
		data->last_error = 1;
		printf("Error: too many arguments to function call\n");
		free_commands(data->commands);
		free_command_list(data->command_list);
		return ;
	}
	print = data->env_c;
	while (print)
	{
		printf("%s\n", print->content);
		print = print->next;
	}
	if (data->n_commands > 1)
	{
		free_commands(data->commands);
		free_command_list(data->command_list);
	}
}
