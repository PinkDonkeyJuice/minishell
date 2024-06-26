/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:03:59 by nchaize-          #+#    #+#             */
/*   Updated: 2024/06/04 15:37:23 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_handle;

int	read_input_heredoc(t_data *data)
{
	char	*line;

	line = readline("$> here_doc: ");
	while (line != NULL)
	{
		if (ft_strcmp(line, data->delimiter) == 0)
		{
			if (close(data->fdin) == -1)
				error(data, "error closing file\n");
			data->fdin = open(data->heredoc_name, O_RDWR | O_CREAT, 0644);
			return (0);
		}
		if (g_signal_handle == SIGINT)
			return (handle_sign_heredoc(data, line), 0);
		line = expand_line(line, data);
		ft_putstr_fd(line, data->fdin);
		ft_putstr_fd("\n", data->fdin);
		free(line);
		line = readline("$> here_doc: ");
	}
	if (line == NULL)
		return (handle_ctrld(data));
	return (0);
}

void	here_doc(t_data *data)
{
	size_t	i;
	bool	stop;
	char	*number;

	i = 0;
	stop = false;
	heredoc_signal_handler(data);
	while (!stop)
	{
		number = ft_itoa(i);
		free(data->heredoc_name);
		data->heredoc_name = ft_strjoin("./.heredoc_", number);
		free(number);
		if (access(data->heredoc_name, F_OK) == -1)
		{
			no_access_heredoc(data);
			stop = true;
		}
		i++;
	}
	read_input_heredoc(data);
	unlink(data->heredoc_name);
	free(data->heredoc_name);
	data->heredoc_name = NULL;
}

void	signal_handler_is_sigint(t_data *data)
{
	g_signal_handle = 0;
	data->last_error = 130;
}

void	handle_operator(t_data *data, size_t i)
{
	char	*command;

	command = data->command_list[i].command;
	if (data->command_list[i].type == TYPE_OPERATOR)
	{
		if (ft_strncmp(command, ">>", 2) == 0)
			data->fdout = open(data->command_list[i + 1].command, \
				O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (ft_strncmp(command, ">", 2) == 0)
			data->fdout = open(data->command_list[i + 1].command, \
				O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (ft_strncmp(command, "<", 2) == 0)
		{
			data->fdin = open(data->command_list[i + 1].command, O_RDONLY);
			if (data->fdin == -1)
				return ;
		}
		if (ft_strncmp(command, "<<", 2) == 0)
		{
			data->delimiter = data->command_list[i + 1].command;
			here_doc(data);
		}
	}
}

int	handle_input_output(t_data *data)
{
	size_t	i;

	data->n_pipe_fdin = 0;
	i = -1;
	data->fdout = STDOUT_FILENO;
	data->fdin = STDIN_FILENO;
	while (data->command_list[++i].command)
	{
		if (data->command_list[i].type == TYPE_PIPE)
			data->n_pipe_fdin++;
		handle_operator(data, i);
	}
	if (data->fdin == -1 || data->fdout == -1)
	{
		ft_putstr_fd("failed to open file\n", 2);
		data->last_error = 1;
		return (-1);
	}
	return (0);
}
