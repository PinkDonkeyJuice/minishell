/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:48:32 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/23 11:42:39 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_var(t_data *data, char *line, char *new_line, t_parse *c)
{
	char	*content;
	t_env	*search;

	search = search_var(&(line[c->i]), data);
	if (search != NULL)
	{
		content = cont_of_var(search->content);
		while (*content != '\0')
		{
			new_line[c->j] = *content;
			if (is_very_specific(new_line[c->j]))
				new_line[c->j] *= -1;
			content++;
			c->j += 1;
		}
	}
	while ((ft_isalnum(line[c->i]) || line[c->i] == '_')
		&& line[c->i])
		c->i += 1;
	if (search == NULL && (line[c->i] == ' ' || line[c->i] == '\0'))
	{
		new_line[c->j] = -32;
		c->j += 1;
	}
}

int	do_dollars(t_data *data, char *line, char *new_line, t_parse *c)
{
	if (line[c->i] == '$')
	{
		if (!ft_isalnum(line[c->i + 1]) && line[c->i + 1] != '_')
		{
			not_an_env_var(data, new_line, &(c->i), &(c->j));
			return (1);
		}
		c->i += 1;
		fill_var(data, line, new_line, c);
		return (1);
	}
	return (0);
}

int	check_var_real(char *line, char *new_line, t_data *data)
{
	t_parse	c;

	c.i = 0;
	c.j = 0;
	while (line[c.i])
	{
		if (line[c.i] == '\'')
			check_var_sq(line, new_line, &(c.i), &(c.j));
		if (line[c.i] == '\"')
		{
			check_var_dq(line, new_line, &(c.i), &(c.j));
			continue ;
		}
		else
		{
			do_dollars(data, line, new_line, &c);
			new_line[c.j] = line[c.i];
		}
		if (line[c.i])
			i_plusplus_j_plusplus(line, &(c.i), &(c.j));
	}
	return (c.j);
}

char	*check_var(char *line, t_data *data)
{
	char	*new_line;
	int		j;
	int		len;

	len = new_line_len(line, data);
	j = 0;
	new_line = malloc(sizeof(char) * (len + 1));
	if (!new_line)
		return (NULL);
	j = check_var_real(line, new_line, data);
	new_line[j] = '\0';
	free(line);
	return (new_line);
}

int	checker(char **line, t_data *data)
{
	if (!check_closed_quotes(*line))
		return (0);
	if (!check_operator(*line))
		return (0);
	*line = check_var(*line, data);
	if (!(*line))
		return (0);
	return (1);
}
