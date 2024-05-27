/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:47:11 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/14 17:47:11 by nchaize-         ###   ########.fr       */
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
	if (line[i] == '|' && line[i + 1] != ' ' && line[i + 1] && i != 0
		&& line[i + 1] != '<' && line[i + 1] != '>')
		*count += 1;
	if (line[i] == '<' && line[i + 1] != '<')
		*count += 1;
	if (line[i] == '<' && line[i + 1] != '<'
		&& line[i + 1] != ' ' && line[i + 1])
		*count += 1;
	if (line[i] == '>' && line[i + 1] != '>')
		*count += 1;
	if (line[i] == '>' && line[i + 1] != '>'
		&& line[i + 1] != ' ' && line[i + 1])
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
