/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:16:18 by gyvergni          #+#    #+#             */
/*   Updated: 2024/04/30 15:19:13 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_back(t_pipe **lst, t_pipe *new)
{
	t_pipe	*cur_list;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			cur_list = *lst;
			while (cur_list->next != NULL)
				cur_list = cur_list->next;
			cur_list->next = new;
		}
	}
}

void	create_pipe(size_t i, t_pipe **pipe_list)
{
	t_pipe	*new;

	new = malloc(sizeof(t_pipe));
	if (!new)
		return ;
	if (pipe(new->p) == -1)
		perror("pipe");
	new->id = i;
	new->next = NULL;
	add_back(pipe_list, new);
}

t_pipe	*access_pipe(t_pipe **pipe_list, size_t i)
{
	size_t	j;
	t_pipe	*cur_pipe;

	cur_pipe = *pipe_list;
	j = 0;
	while (j != i)
	{
		cur_pipe = cur_pipe->next;
		j++;
	}
	return (cur_pipe);
}

void	generate_pipes(t_pipe **pipe_list, t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->n_commands - 1)
	{
		create_pipe(i, pipe_list);
		i++;
	}
	data->pipe_list = pipe_list;
}

void	close_pipes(t_data *data, t_pipe **pipe_list, size_t i, size_t j)
{
	size_t	fd;

	fd = 0;
	while (fd < data->n_commands - 1)
	{
		if (fd != j && fd != i)
		{
			close(access_pipe(pipe_list, fd)->p[0]);
			close(access_pipe(pipe_list, fd)->p[1]);
		}
		fd++;
	}
}
