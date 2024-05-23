/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:45:13 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/23 14:48:46 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_in_quotes(char *line, int *i)
{
	if (line[*i] == '\"')
	{
		*i += 1;
		while (line[*i] != '\"')
			*i += 1;
	}
	if (line[*i] == '\'')
	{
		*i += 1;
		while (line[*i] != '\'')
			*i += 1;
	}
}

void	pipe_checker(char *line, int *i, int *p)
{
	if (line[*i] == '|' && line[*i + 1] && *p == 0)
	{
		*p = 1;
		*i += 1;
	}
}

int	check_pipes(char *line)
{
	int	i;
	int	p;

	i = 0;
	p = 0;
	while (line[i])
	{
		pipe_in_quotes(line, &i);
		pipe_checker(line, &i, &p);
		if (line[i] == '|' && p == 1)
		{
			if (line[i] == '|')
				printf("minishell: syntax error near unexpected token \'|\'\n");
			return (0);
		}
		if (line[i] != '|' && line[i] != ' ')
			p = 0;
		i++;
	}
	return (1);
}