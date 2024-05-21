/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pinkdonkeyjuice <pinkdonkeyjuice@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:03:59 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/21 16:02:12 by pinkdonkeyj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_handle;

void	read_input_heredoc(t_data *data)
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
			return ;
		}
		if (g_signal_handle == SIGINT)
		{
			signal_handler_is_sigint(data);
			return ((void) free(line));
		}
		line = expand_line(line, data);
		ft_putstr_fd(line, data->fdin);
		ft_putstr_fd("\n", data->fdin);
		line = readline("$> here_doc: ");
	}
	if (line == NULL)
	{
		printf("warning: here_doc ended with EOF\n");
		/* unlink(data->heredoc_name);
		free(data->heredoc_name); */
	}
}

void	here_doc(t_data *data)
{
	size_t	i;
	bool	stop;
	char	*number;

	i = 0;
	stop = false;
	heredoc_signal_handler();
	while (!stop)
	{
		number = ft_itoa(i);
		data->heredoc_name = ft_strjoin("./.heredoc_", number);
		free(number);
		if (access(data->heredoc_name, F_OK) == -1)
		{
			data->fdin = open(data->heredoc_name, O_RDWR | O_CREAT, 0644);
			if (data->fdin == -1)
			{
				free(data->heredoc_name);
				error(data, "error opening heredoc input file\n");
			}
			stop = true;
		}
		i++;
	}
	read_input_heredoc(data);
}

void	signal_handler_is_sigint(t_data *data)
{
	g_signal_handle = 0;
	data->last_error = 130;
	if (close(data->fdin) == -1)
		error(data, "error closing file\n");
	data->fdin = open(data->heredoc_name, O_RDWR | O_CREAT, 0644);
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
		if (ft_strncmp(command, ">", 2) == 0)
			data->fdout = open(data->command_list[i + 1].command, \
				O_RDWR | O_TRUNC | O_CREAT, 0644);
	}
}

int	handle_input_output(t_data *data)
{
	size_t	i;

	i = -1;
	data->fdout = STDOUT_FILENO;
	data->fdin = STDIN_FILENO;
	while (data->command_list[++i].command)
		handle_operator(data, i);
	if (data->fdin == -1 || data->fdout == -1)
	{
		ft_putstr_fd("failed to open file\n", 2);
		data->last_error = 1;
		return (-1);
	}
	return (0);
}
