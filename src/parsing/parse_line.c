/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:47:29 by nchaize-          #+#    #+#             */
/*   Updated: 2024/04/29 12:26:51 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_args_utils(char *line, int i, int *count)
{
	if ((line[i + 1] != ' ' && line[i] == ' ' && line[i + 1] != '|'
			&& line[i + 1] != '<' && line[i + 1] != '>' && line[i + 1] != '\0')
		|| (i == 0 && line[i] != ' ' && line[i] != '<' && line[i] != '>'))
	{
		*count += 1;
	}
	if (line[i] == '|' && i != 0)
		*count += 1;
	if (line[i] == '|' && line[i + 1] != ' ' && line[i + 1] && i != 0)
		*count += 1;
	if (line[i] == '<' && line[i + 1] != '<' && i != 0)
		*count += 1;
	if (line[i] == '<' && line[i + 1] != '<'
		&& line[i + 1] != ' ' && line[i + 1] && i != 0)
		*count += 1;
	if (line[i] == '>' && line[i + 1] != '>' && i != 0)
		*count += 1;
	if (line[i] == '>' && line[i + 1] != '>'
		&& line[i + 1] != ' ' && line[i + 1] && i != 0)
		*count += 1;
}

int	count_args(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		count_args_utils(line, i, &count);
		if (line[i] == '\"')
		{
			i++;
			while (line[i] && line[i] != '\"')
				i++;
		}
		if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
		}
		i++;
	}
	return (count);
}

void	len_to_next_utils(char *line, int *i)
{
	while (line[*i])
	{
		if (line[*i] == '\"')
		{
			*i += 1;
			while (line[*i] && line[*i] != '\"')
				*i += 1;
		}
		if (line[*i] == '\'')
		{
			*i += 1;
			while (line[*i] && line[*i] != '\'')
				*i += 1;
		}
		if (line[*i] == ' ' || line[*i] == '|'
			|| line[*i] == '<' || line[*i] == '>')
			return ;
		*i += 1;
	}
}

void	while_space(char *line, int *i)
{
	while (line[*i] == ' ')
		*i += 1;
}

int	len_to_next(char *line, int i)
{
	while_space(line, &i);
	if (line[i] == '|')
	{
		i++;
		if (line[i] != ' ')
			return (i);
	}
	if (line[i] == '<')
	{
		i++;
		if (line[i] == '<')
			i++;
		if (line[i] != ' ')
			return (i);
	}
	if (line[i] == '>')
	{
		i++;
		if (line[i] == '>')
			i++;
		if (line[i] != ' ')
			return (i);
	}
	len_to_next_utils(line, &i);
	return (i);
}

void	len_of_arg_utils_utils(char *line, int *i, int *g, int *g2)
{
	if (line[*i] == '\"' && *g == 0 && *g2 == 0)
	{
		*g = 1;
		*i += 1;
	}
	if (line[*i] == '\'' && *g2 == 0 && *g == 0)
	{
		*g2 = 1;
		*i += 1;
	}
}

int	len_of_arg_utils(char *line, int i, int *count)
{
	int	g;
	int	g2;

	g = 0;
	g2 = 0;
	while (line[i])
	{
		if ((line[i] == ' ' || line[i] == '|'
				|| line[i] == '<' || line[i] == '>')
			&& g == 0 && g2 == 0)
			return (*count);
		len_of_arg_utils_utils(line, &i, &g, &g2);
		if (line[i] == '\"' && g == 1 && g2 == 0)
			g = 0;
		if (line[i] == '\'' && g2 == 1 && g == 0)
			g2 = 0;
		if ((line[i] != '\"' && line[i] != '\'')
			|| (line[i] == '\"' && g2 == 1) || (line[i] == '\'' && g == 1))
			*count += 1;
		i++;
	}
	return (*count);
}

int	len_of_arg(char *line)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '|')
		count++;
	if (line[i] == '<')
	{
		count++;
		if (line[i + 1] == '<')
			count++;
	}
	if (line[i] == '>')
	{
		count++;
		if (line[i + 1] == '>')
			count++;
	}
	len_of_arg_utils(line, i, &count);
	return (count);
}

static void	free_all(t_command *to_free, int i_words)
{
	while (i_words >= 0)
	{
		free(to_free[i_words].command);
		i_words--;
	}
	free(to_free);
}

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

t_command	write_string(char *line, int len)
{
	int			i;
	int			j;
	t_command	send;

	i = 0;
	j = 0;
	send.type = 0;
	send.command = malloc(sizeof(char) * len + 1);
	while (line[i] == ' ')
		i++;
	while (j < len)
	{
		write_string_utils(line, send, &i, &j);
		if (line[i] != '\"' && line[i] != '\'')
		{
			send.command[j] = line[i];
			if (send.command[j] == '<' || send.command[j] == '>')
				send.type = TYPE_OPERATOR;
			if (send.command[j] == '|')
				send.type = TYPE_PIPE;
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
		return (change_last_error(data, 2), NULL);
	args = count_args(line);
	parsed = malloc(sizeof(t_command) * (args + 1));
	if (!parsed)
		return (NULL);
	while (j < args)
	{
		parsed[j] = write_string(&line[i], len_of_arg(&line[i]));
		if (!parsed[j].command)
			return (free_all(parsed, j), NULL);
		i += len_to_next(&line[i], 0);
		j++;
	}
	parsed[j].command = NULL;
	return ((free(line), finish_parsing(parsed)));
}
