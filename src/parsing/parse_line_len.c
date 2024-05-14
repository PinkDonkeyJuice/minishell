/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:06:29 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/14 18:06:29 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
