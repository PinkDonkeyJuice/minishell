/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:52:38 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/02 13:05:03 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env	*env)
{
	t_env 	*node;
	t_env	*next;

	if (!env)
		return ;
	node = env;
	while (node && node->content != NULL)
	{
		next = node->next;
		free(node);
		node = next;
	}
	//free(env);
}

void	free_pipes(t_pipe **pipe_list)
{
	t_pipe	*node;
	t_pipe	*next;

	if (pipe_list && *pipe_list)
	{
		node = *pipe_list;
		while (node != NULL)
		{
			next = node->next;
			free(node);
			node = next;
		}
	}
}

void	free_command_list(t_command *command_list)
{
	size_t		i;

	i = 0;
	if (command_list == NULL)
		return ;
	while (command_list[i].command)
	{
		free(command_list[i].command);
		i++;
	}
	free(command_list);
}

void	free_all(t_data *data)
{
	free_commands(data->commands);
	free_command_list(data->command_list);
	free_env(data->env_c);
	//free(data->line);
}