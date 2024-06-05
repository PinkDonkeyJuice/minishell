/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:49:47 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/14 18:49:47 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_line(char *line, t_data *data)
{
	int	i;

	i = 0;
	line = check_var(line, data);
	while (line[i])
	{
		if (line[i] == -11)
			line[i] = 0;
		if (line[i] < 0)
			line[i] *= -1;
		i++;
	}
	return (line);
}

void	no_access_heredoc(t_data *data)
{
	data->fdin = open(data->heredoc_name, O_RDWR | O_CREAT, 0644);
	if (data->fdin == -1)
	{
		free(data->heredoc_name);
		error(data, "error opening heredoc input file\n");
	}
}

void	handle_sign_heredoc(t_data *data, char *line)
{
	signal_handler_is_sigint(data);
	free(line);
}

int	handle_ctrld(t_data *data)
{
	if (close(data->fdin) == -1)
		error(data, "error closing file\n");
	data->fdin = open(data->heredoc_name, O_RDWR | O_CREAT, 0644);
	printf("warning: here_doc ended with EOF (wanted \'%s\')\n",
		data->delimiter);
	return (1);
}
