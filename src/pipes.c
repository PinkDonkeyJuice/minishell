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
	int		pip[2];

	if (pipe(pip) == -1)
		perror("pipe");
	new = malloc(sizeof(t_pipe));
	if (!new)
		return ;
	new->id = i;
	new->p[0] = pip[0];
	new->p[1] = pip[1];
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
	size_t i;

	i = 0;
	while (i < data->n_commands - 1)
	{
		create_pipe(i, pipe_list);
		i++;
	}
}

void	close_pipes(t_data *data, t_pipe **pipe_list)
{
	size_t 	i;
	
	i = 0;
	while (i < data->n_commands - 1)
	{
		close(access_pipe(pipe_list, i)->p[0]);
		close(access_pipe(pipe_list, i)->p[1]);
		i++;
	}
}