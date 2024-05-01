/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pinkdonkeyjuice <pinkdonkeyjuice@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:55:09 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/01 20:47:01 by pinkdonkeyj      ###   ########.fr       */
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

	if (pipe_list == NULL)
		return ;
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

void	free_all(t_data *data)
{
	write(1, "a\n", 2);
	free_pipes(data->pipe_list);
	write(1, "b\n", 2);
	/* free_commands(data->commands);
	free_env(data->env_c); */
	//free(data->line);

}

void	close_safe( t_data *data, int fd)
{
	if (close(fd) == -1)
	{
		free_all(data);
		perror("Closing file: ");
		exit(-1);
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
