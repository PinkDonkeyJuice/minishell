/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:31:06 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/14 17:31:06 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_heredoc(char *line, char *new_line, t_parse *c, int *h)
{
	new_line[c->j] = line[c->i];
	c->i += 1;
	c->j += 1;
	new_line[c->j] = line[c->i];
	if (line[c->i] == '<')
	{
		*h = 1;
		return (1);
	}
	return (0);
}

void	op_in_quotes(char *line, int *i)
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

void	op_checker(char *line, int *i, int *o)
{
	if (line[*i] == '>' && line[*i + 1] && *o == 0)
	{
		*o = 1;
		*i += 1;
		if (line[*i] == '>')
			*i += 1;
	}
	if (line[*i] == '<' && line[*i + 1] && *o == 0)
	{
		*o = 1;
		*i += 1;
		if (line[*i] == '<')
			*i += 1;
	}
}

int	check_operator(char *line)
{
	int	i;
	int	o;

	i = 0;
	o = 0;
	while (line[i])
	{
		op_in_quotes(line, &i);
		op_checker(line, &i, &o);
		if ((line[i] == '>' || line[i] == '<') && o == 1)
		{
			if (line[i] == '>')
				printf("minishell: syntax error near unexpected token \'>\'\n");
			if (line[i] == '<')
				printf("minishell: syntax error near unexpected token \'<\'\n");
			return (0);
		}
		if (line[i] != '>' && line[i] != '<' && line[i] != ' ')
			o = 0;
		i++;
	}
	return (1);
}
