/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:03:59 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/14 17:27:10 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_handle;

char	*expand_line(char *line, t_data *data)
{
	int	i;

	i = 0;
	line = check_var(line, data);
	while (line[i])
	{
		if (line[i] < 0)
			line[i] *= -1;
		i++;
	}
	return (line);
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
