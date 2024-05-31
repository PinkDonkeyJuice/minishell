/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:47:29 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/31 14:08:15 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_string_utils(char *line, t_command send, int *i, int *j)
{
	if (line[*i] == '\"')
	{
		*i += 1;
		while (line[*i] != '\"')
		{
			send.command[*j] = line[*i];
			*j += 1;
			*i += 1;
		}
	}
	if (line[*i] == '\'')
	{
		*i += 1;
		while (line[*i] != '\'')
		{
			send.command[*j] = line[*i];
			*j += 1;
			*i += 1;
		}
	}
}

t_command	end_string(t_command send, int j)
{
	send.command[j] = '\0';
	return (send);
}

void	write_type(t_command *send, int j)
{
	if (send->command[j] == '<' || send->command[j] == '>')
		send->type = TYPE_OPERATOR;
	if (send->command[j] == '|')
		send->type = TYPE_PIPE;
}

t_command	write_string(char *line, int len)
{
	int			i;
	int			j;
	t_command	send;

	i = 0;
	j = 0;
	send.type = 0;
	send.command = malloc(sizeof(char) * len + 1);
	if (!send.command)
		return (send);
	while (line[i] == ' ')
		i++;
	while (j < len)
	{
		write_string_utils(line, send, &i, &j);
		if (line[i] != '\"' && line[i] != '\'')
		{
			send.command[j] = line[i];
			write_type(&send, j);
			j++;
		}
		i++;
	}
	return (end_string(send, j));
}

t_command	*parse_line(char *line, t_data *data)
{
	int			i;
	int			j;
	t_command	*parsed;
	int			args;

	i = 0;
	j = 0;
	if (!checker(&line, data))
		return (free(line), data->last_error = 2, NULL);
	args = count_args(line);
	parsed = malloc(sizeof(t_command) * (args + 1));
	if (!parsed)
		return (NULL);
	while (j < args)
	{
		parsed[j] = write_string(&line[i], len_of_arg(&line[i]));
		if (!parsed[j].command)
			return (free_parsing(parsed, j), NULL);
		i += len_to_next(&line[i], 0);
		j++;
	}
	parsed[j].command = NULL;
	if (!last_check(parsed))
		return (free(line), free_parsing(parsed, j), NULL);
	return ((free(line), finish_parsing(parsed)));
}
