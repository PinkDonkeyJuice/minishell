/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:48:32 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/15 14:17:41 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_var(t_data *data, char *new_line, int *i, int *j)
{
	char	*content;
	t_env	*search;

	search = search_var(&(data->line[*i]), data);
	if (search != NULL)
	{
		content = cont_of_var(search->content);
		while (*content != '\0')
		{
			new_line[*j] = *content;
			if (is_very_specific(new_line[*j]))
				new_line[*j] *= -1;
			content++;
			*j += 1;
		}
	}
	while ((ft_isalnum(data->line[*i]) || data->line[*i] == '_')
		&& data->line[*i])
		*i += 1;
	if (search == NULL && (data->line[*i] == ' ' || data->line[*i] == '\0'))
	{
		new_line[*j] = -32;
		*j += 1;
	}
}

int	do_dollars(t_data *data, char *new_line, int *i, int *j)
{
	if (data->line[*i] == '$')
	{
		if (!ft_isalnum(data->line[*i + 1]))
		{
			not_an_env_var(data, new_line, i, j);
			return (1);
		}
		*i += 1;
		fill_var(data, new_line, i, j);
		return (1);
	}
	return (0);
}

int	check_var_real(char *line, char *new_line, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			check_var_sq(line, new_line, &i, &j);
		if (line[i] == '\"')
		{
			check_var_dq(line, new_line, &i, &j);
			continue ;
		}
		else
		{
			do_dollars(data, new_line, &i, &j);
			new_line[j] = line[i];
		}
		if (line[i])
			i_plusplus_j_plusplus(line, &i, &j);
	}
	return (j);
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
