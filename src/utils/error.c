/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:55:09 by gyvergni          #+#    #+#             */
/*   Updated: 2024/04/30 15:25:44 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env	*env)
{
	t_env 	*node;
	t_env	*next;

	node = env;
	while (node->content != NULL)
	{
		free(node->content);
		next = node->next;
		free(node);
		node = next;
	}
	free(env);
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
		free(pipe_list);
	}
}

void	error(t_data *data, char *err_msg)
{
	free(data->line);
	free_commands(data->commands);
	free_env(data->env_c);
	free_pipes(data->pipe_list);
	ft_putstr_fd(err_msg, 2);	
}
