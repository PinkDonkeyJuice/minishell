/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:26:03 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/14 17:10:20 by nchaize-         ###   ########.fr       */
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
	if (is_builtin(data) == 0 && data->n_commands > 1)
		close_safe(data,
			access_pipe(data->pipe_list, data->n_commands - 1)->p[0]);
	if (i == data->n_commands - 1)
		write(access_pipe(data->pipe_list, data->n_commands - 1)->p[1],
			&(data->last_error), sizeof(int));
	if (is_builtin(data) == 0 && data->n_commands > 1)
		close_safe(data,
			access_pipe(data->pipe_list, data->n_commands - 1)->p[1]);
}


void	exec(t_data *data, size_t i)
{
	char	*path;

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
		execve(path, data->commands, data->env);
	}
	redir_lasterror(data, i);
	if (data->env_c)
		free_env(data->env_c);
	free_pipes(data->pipe_list);
	exit(1);
}

void	mark_status(int status, t_data *data, bool *forcequit)
{
	int	term_sig;

	//printf("Status : %d\n Exit status : %d\n\n", status, WEXITSTATUS(status));
	if (WEXITSTATUS(status) != 0 && is_builtin(data) == 0)
		data->last_error = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		term_sig = WTERMSIG(status);
		if (term_sig == SIGQUIT)
		{
			data->last_error = 131;
		}
		else if (term_sig == SIGINT)
		{
			data->last_error = 130;
		}
		*forcequit = true;
	}
}

size_t	count_pipes(t_command *command_list)
{
	size_t	n;
	size_t	i;

	n = 1;
	i = 0;
	if (command_list == NULL)
		return (0);
	while (command_list[i].command != NULL)
	{
		if (command_list[i].type == TYPE_PIPE)
			n++;
		i++;
	}
	return (n);
}
