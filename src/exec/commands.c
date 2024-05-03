/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:23:11 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/03 11:32:17 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_commands(char **commands)
{
	size_t	i;

	i = 0;
	if (commands == NULL)
		return ;
	while (commands[i])
	{
		free(commands[i]);
		i++;
	}
	free(commands);
	return ;
}

void	print_commands(char	**commands)
{
	size_t i;

	i = 0;
	if (commands == NULL)
	{
		printf("Commands is null");
		return ;
	}
	while (commands[i])
	{
		printf("Command %zu is: %s\n", i, commands[i]);
		i++;
	}
	printf("Command %zu is: %s\n", i, commands[i]);
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
	handle_input_output(data);
	printf("fdin : %d, fdout: %d\n", data->fdin, data->fdout);
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
		//waitpid(parent, NULL, 0);
		child_process(data, pipe_list, i);
	}
	if (parent > 0)
		parent_process(data, pipe_list);
}
