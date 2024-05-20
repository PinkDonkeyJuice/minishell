/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:28:08 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/14 17:28:08 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	closed_quotes(char *line, int *g1, int *g2)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' && *g1 == 0 && *g2 == 0)
		{
			*g1 = 1;
			i++;
		}
		if (line[i] == '\'' && *g2 == 0 && *g1 == 0)
		{
			*g2 = 1;
			i++;
		}
		if (line[i] == '\'' && *g2 == 1 && *g1 == 0)
			*g2 = 0;
		if (line[i] == '\"' && *g1 == 1 && *g2 == 0)
			*g1 = 0;
		if (line[i])
			i++;
	}
}

int	check_closed_quotes(char *line)
{
	int	g1;
	int	g2;

	g1 = 0;
	g2 = 0;
	closed_quotes(line, &g1, &g2);
	if (g1 == 0 && g2 == 0)
		return (1);
	else
		return (printf("minishell: syntax error\n"), 0);
}

void	i_plusplus_j_plusplus(char *line, int *i, int *j)
{
	if (line[*i] != '\0' && line[*i] != '$')
	{
		*i += 1;
		*j += 1;
	}
}
