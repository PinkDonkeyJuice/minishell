/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:22:54 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/14 17:22:54 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"

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
	free(data->heredoc_name);
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
