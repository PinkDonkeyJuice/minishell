/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:38:59 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/15 13:57:32 by nchaize-         ###   ########.fr       */
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
	free_commands(data->commands);
	free_command_list(data->command_list);
}
