/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_lentonext.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:02:38 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/14 18:02:38 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_parsing(t_command *to_free, int i_words)
{
	while (i_words >= 0)
	{
		free(to_free[i_words].command);
		i_words--;
	}
	free(to_free);
}
