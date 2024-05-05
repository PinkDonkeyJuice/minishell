/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pinkdonkeyjuice <pinkdonkeyjuice@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:52:38 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/05 19:29:06 by pinkdonkeyj      ###   ########.fr       */
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
	while (node)
	{
		next = node->next;
		free(node->content);
		free(node);
		node = next;
	}
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
	if (!command_list)
		return ;
	while (command_list[i].command)
	{
		free(command_list[i].command);
		i++;
	}
	free(command_list);
}

void	free_all_comms(t_data *data)
{
	free_commands(data->commands);
	free_command_list(data->command_list);
}

void	free_all(t_data *data)
{
	free_commands(data->commands);
	//if (data->n_commands == 1 || data->i_command == data->n_commands)
	free_command_list(data->command_list);
	if (data->n_commands > 1)
		free_pipes(data->pipe_list);
	free_env(data->env_c);
}
