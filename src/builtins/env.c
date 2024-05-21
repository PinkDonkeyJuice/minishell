/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pinkdonkeyjuice <pinkdonkeyjuice@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:38:59 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/21 14:35:17 by pinkdonkeyj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_assigned(char *content)
{
	size_t	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

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
		if (is_assigned(print->content))
			printf("%s\n", print->content);
		print = print->next;
	}
	free_commands(data->commands);
	free_command_list(data->command_list);
}
