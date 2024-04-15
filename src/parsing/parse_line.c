/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:47:29 by nchaize-          #+#    #+#             */
/*   Updated: 2024/04/15 14:16:19 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int        count_args(char *line)
{
    int        i;
    int        count;

    i = 0;
    count = 0;
    while (line[i])
    {
        if ((line[i + 1] != ' ' && line[i] == ' ' && line[i + 1] != '|'
			&& line[i + 1] != '<' && line[i + 1] != '>')
            || (i == 0 && line[i] != ' '))
        {
            count++;
        }
        if (line[i] == '|')
            count++;
        if (line[i] == '|' && line[i + 1] != ' ' && line[i + 1])
            count++;
		if (line[i] == '<' && line[i + 1] != '<')
        	count++;
		if (line[i] == '<' && line[i + 1] != '<'
			&& line[i + 1] != ' ' && line[i + 1])
            count++;
		if (line[i] == '>' && line[i + 1] != '>')
        	count++;
		if (line[i] == '>' && line[i + 1] != '>'
			&& line[i + 1] != ' ' && line[i + 1])
            count++;
        if (line[i] == '\"')
        {
            i++;
            while(line[i] && line[i] != '\"')
                i++;
        }
        if (line[i] == '\'')
        {
            i++;
            while(line[i] && line[i] != '\'')
                i++;
        }
        i++;
    }
    return (count);
}

int	len_to_next(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
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
	while (line[i])
	{
		if (line[i] == '\"')
        {
            i++;
            while(line[i] && line[i] != '\"')
                i++;
        }
        if (line[i] == '\'')
        {
            i++;
            while(line[i] && line[i] != '\'')
                i++;
        }
		if (line[i] == ' ' || line[i] == '|'
			|| line[i] == '<' || line[i] == '>')
			return (i);
		i++;
	}
	return (i);
}

int	len_of_arg(char *line)
{
	int		i;
	int		count;
	int	g;
	int	g2;

	count = 0;
	i = 0;
	g = 0;
	g2 = 0;
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
	while (line[i])
	{
		if ((line[i] == ' ' || line[i] == '|'
			|| line[i] == '<' || line[i] == '>')
			&& g == 0 && g2 == 0)
			return (count);
		if (line[i] == '\"' && g == 0 && g2 == 0)
		{
			g = 1;
			i++;
		}
		if (line[i] == '\'' && g2 == 0 && g == 0)
		{
			g2 = 1;
			i++;
		}
		if (line[i] == '\"' && g == 1 && g2 == 0)
			g = 0;
		if (line[i] == '\'' && g2 == 1 && g == 0)
			g2 = 0;
		if ((line[i] != '\"' && line[i] != '\'') ||
			(line[i] == '\"' && g2 == 1) || (line[i] == '\'' && g == 1))
			count++;
		i++;
	}
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

t_command	write_string(char *line, int len)
{
	int		i;
	int		j;
	t_command	send;

	i = 0;
	j = 0;
	send.op = 0;
	send.command = malloc(sizeof(char) * len + 1);
	while (line[i] == ' ')
		i++;
	while (j < len)
	{
		if (line[i] == '\"')
		{
			i++;
			while (line[i] != '\"')
			{
				send.command[j] = line[i];
				j++;
				i++;
			}
		}		
		if (line[i] == '\'')
		{
			i++;
			while (line[i] != '\'')
			{
				send.command[j] = line[i];
				j++;
				i++;
			}
		}
		if (line[i] != '\"' && line[i] != '\'')
		{
			send.command[j] = line[i];
			if (send.command[j] == '<' || send.command[j] == '>')
				send.type = 3;
			if (send.command[j] == '|')
				send.type = 2;
			j++;
		}
		i++;
	}
	send.command[j] = '\0';
	return (send);
}

t_command	*parse_line(char *line, t_data *data)
{
	int			i;
	int			j;
	t_command *parsed;
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
		i += len_to_next(&line[i]);
		j++;
	}
	parsed[j].command = NULL;
	return (parsed);
}
