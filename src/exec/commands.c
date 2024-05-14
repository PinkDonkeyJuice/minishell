/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:23:11 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/13 14:02:10 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_commands(char **commands)
{
	size_t	i;

	i = 0;
	if (!commands)
		return ;
	while (commands[i])
	{
		free(commands[i]);
		i++;
	}
	free(commands);
	return ;
}

char	**fill_commands(t_command *command_list, size_t i_start, size_t n)
{
	char	**commands;
	size_t	j;

	commands = (char **)malloc(sizeof(char *) * (n + 1));
	if (!commands)
		return (NULL);
	j = 0;
	while (j != n)
	{
		if (command_list[i_start + j].type != TYPE_OPERATOR && \
			((i_start + j == 0) || \
				command_list[i_start + j - 1].type != TYPE_OPERATOR))
		{
			commands[j] = ft_strdup(command_list[i_start + j].command);
			if (!commands[j])
				return (free_commands(commands), NULL);
			j++;
		}
		else
			i_start++;
	}
	commands[n] = NULL;
	return (commands);
}

char	**get_commands(t_command *cl, size_t i)
{
	size_t	i_pipe;
	size_t	i_start;
	size_t	n;
	size_t	j;

	i_start = 0;
	i_pipe = 0;
	if (!cl)
		return (NULL);
	while (i_pipe != i)
	{
		if (cl[i_start].type == TYPE_PIPE)
			i_pipe++;
		i_start++;
	}
	n = 0;
	j = 0;
	while (cl[i_start + j].command != NULL && cl[i_start + j].type != TYPE_PIPE)
	{
		if (cl[i_start + j].type != TYPE_OPERATOR && \
			((i_start + j == 0) || cl[i_start + j - 1].type != TYPE_OPERATOR))
			n++;
		j++;
	}
	return (fill_commands(cl, i_start, n));
}

void	exec_commands(t_data *data)
{
	t_pipe	*pipe_list;

	signal(SIGINT, SIG_IGN);
	if (handle_input_output(data) == -1)
		return ;
	pipe_list = NULL;
	generate_pipes(&pipe_list, data);
	handle_commands(data, &pipe_list);
	signal_handler();
}

void	handle_commands(t_data *data, t_pipe **pipe_list)
{
	pid_t	parent;
	size_t	i;

	i = 0;
	parent = 1;
	while (i < data->n_commands && parent)
	{
		if (parent)
			parent = fork();
		if (parent)
			i++;
		if (parent < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
	}
	if (parent == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		child_process(data, pipe_list, i);
	}
	if (parent > 0)
		parent_process(data, pipe_list);
}
