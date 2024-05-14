/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_parse_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:35:47 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/14 17:35:47 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_in_quote(char *line, int i)
{
	int	j;
	int	g;

	j = 0;
	g = 0;
	while (line[j] && j != i)
	{
		if (line[j] == '\"' && g == 0)
		{
			g = 1;
			j++;
		}
		if (line[j] == '\"' && g == 1)
		{
			g = 0;
			j++;
		}
		if (line[j])
			j++;
	}
	return (g);
}

void	check_var_sq(char *line, char *new_line, int *i, int *j)
{
	new_line[*j] = line[*i];
	*i += 1;
	*j += 1;
	if (check_in_quote(line, *i))
		return ;
	while (line[*i] != '\'' && line[*i])
	{
		new_line[*j] = line[*i];
		*i += 1;
		*j += 1;
	}
	new_line[*j] = line[*i];
	*i += 1;
	*j += 1;
	return ;
}

int	check_var_dq(char *line, char *new_line, int *i, int *j)
{
	new_line[*j] = line[*i];
	*i += 1;
	*j += 1;
	if (!line[*i])
		return (0);
	while (line[*i] != '\"' && line[*i] && line[*i] != '$')
	{
		new_line[*j] = line[*i];
		*i += 1;
		*j += 1;
	}
	if (line[*i] == '$')
		return (1);
	new_line[*j] = line[*i];
	*i += 1;
	*j += 1;
	return (0);
}

void	not_an_env_var(t_data *data, char *new_line, int *i, int *j)
{
	char	*num;
	int		index;

	index = 0;
	if (data->line[*i + 1] == '?')
	{
		*i += 2;
		num = ft_itoa(data->last_error);
		while (num[index])
		{
			new_line[*j] = num[index];
			index++;
			*j += 1;
		}
		free(num);
		return ;
	}
	new_line[*j] = data->line[*i];
	*i += 1;
	*j += 1;
	return ;
}

int	is_very_specific(char c_new_line)
{
	if (c_new_line == '\"' || c_new_line == '\''
		|| c_new_line == '|' || c_new_line == '<'
		|| c_new_line == '>')
		return (1);
	return (0);
}
