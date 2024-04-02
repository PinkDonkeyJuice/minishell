/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pinkdonkeyjuice <pinkdonkeyjuice@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:47:29 by nchaize-          #+#    #+#             */
/*   Updated: 2024/03/22 16:22:13 by pinkdonkeyj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_args(char *line)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if ((line[i + 1] != ' ' && line[i] == ' ')
			|| (i == 0 && line[i] != ' '))
		{
			count++;
		}
		if (line[i] == '\"')
		{
			i++;
			while(line[i] && line[i] != '\"')
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
	while (line[i])
	{
		if (line[i] == ' ')
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

	count = 0;
	i = 0;
	g = 0;
	while (line[i] == ' ')
		i++;
	while (line[i])
	{
		if (line[i] == ' ' && g == 0)
			return (count);
		if (line[i] == '\"' && g == 0)
		{
			g = 1;
			i++;
		}
		if (line[i] == '\"' && g == 1)
			g = 0;
		if (line[i] != '\"')
			count++;
		i++;
	}
	return (count);
}

static void	free_all(char **to_free, int i_words)
{
	while (i_words >= 0)
	{
		free(to_free[i_words]);
		i_words--;
	}
	free(to_free);
}

char	*write_string(char *line, int len)
{
	int		i;
	int		j;
	char	*send;

	i = 0;
	j = 0;
	send = malloc(sizeof(char) * len + 1);
	while (line[i] == ' ')
		i++;
	while (j < len)
	{
		if (line[i] != '\"')
		{
			send[j] = line[i];
			j++;
		}
		i++;
	}
	send[j] = '\0';
	return (send);
}

char	**parse_line(char *line)
{
	int		i;
	int		j;
	char	**parsed;
	int		lenarg;
	int		args;

	i = 0;
	j = 0;
	args = count_args(line);
	parsed = malloc(sizeof(char *) * (args + 1));
	if (!parsed)
		return (NULL);
	while (j < args)
	{
		lenarg = len_of_arg(&line[i]);
		parsed[j] = write_string(&line[i], lenarg);
		if (!parsed[j])
			return (free_all(parsed, i), NULL);
		i += len_to_next(&line[i]);
		j++;
	}
	parsed[j] = NULL;
	return (parsed);
}
