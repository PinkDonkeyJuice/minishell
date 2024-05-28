/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:26:03 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/27 14:59:40 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_no_commands(void)
{
	printf("Memory allocation problem encountered during get_commands_\n");
	exit(-1);
}

void	redir_lasterror(t_data *data, size_t i)
{
	if (data->n_commands > 1)
		close_safe(data,
			access_pipe(data->pipe_list, data->n_commands - 1)->p[0]);
	if (i == data->n_commands - 1)
		write(access_pipe(data->pipe_list, data->n_commands - 1)->p[1],
			&(data->last_error), sizeof(int));
	if (data->n_commands > 1)
		close_safe(data,
			access_pipe(data->pipe_list, data->n_commands - 1)->p[1]);
	if (i == data->n_commands - 1)
		free_pipes(data->pipe_list);
}

size_t	count_env_var(t_data *data)
{
	size_t	n;
	t_env	*node;

	n = 0;
	node = data->env_c;
	while (node && node->content)
	{
		n++;
		node = node->next;
	}
	return (n);
}

char	**recreate_env(t_data *data)
{
	char	**new_env;
	size_t	i;
	t_env	*node;

	new_env = malloc(sizeof(char *) * (count_env_var(data) + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	node = data->env_c;
	while (node && node->content)
	{
		new_env[i] = ft_strdup(node->content);
		node = node->next;
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	exec(t_data *data, size_t i)
{
	char	*path;
	char	**new_env;

	free_commands(data->commands);
	data->commands = get_commands(data->command_list, i);
	if (data->commands == NULL)
		do_no_commands();
	data->i_command = i;
	if (check_builtins(data) == 0)
	{
		path = get_exec_path(data->commands[0], data);
		if (data->fdin != STDIN_FILENO)
			close_safe(data, data->fdin);
		redir_lasterror(data, i);
		if (path == NULL)
		{
			free_env(data->env_c);
			if (i != data->n_commands - 1)
				free_pipes(data->pipe_list);
			exit(127);
		}
		new_env = recreate_env(data);
		if (new_env == NULL)
			error(data, "Memory allocation failure\n");
		execve(path, data->commands, new_env);
	}
	else
	{
		free_env(data->env_c);
		redir_lasterror(data, i);
	}
	if (i != data->n_commands - 1)
		free_pipes(data->pipe_list);
	free_all_comms(data);
	exit(1);
}
