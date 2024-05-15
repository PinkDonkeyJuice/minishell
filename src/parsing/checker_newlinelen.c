/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_newlinelen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:32:30 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/14 17:32:30 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_line_len_base_utils(char *line, int *i, int *len, int *g)
{
	if (line[*i] == '\"' && *g == 0)
	{
		*g = 1;
		*len += 1;
		*i += 1;
	}
	if (line[*i] == '\"' && *g == 1)
	{
		*g = 0;
		*len += 1;
		if (line[*i + 1])
			*i += 1;
	}
}

void	new_line_len_base(char *line, int *i, int *len)
{
	static int	g = 0;

	new_line_len_base_utils(line, i, len, &g);
	if (line[*i] != '$' && line[*i] != '\'' && line[*i] != '\"' && line[*i])
		*len += 1;
	if (line[*i] == '\'')
	{
		*len += 1;
		if (g == 1)
			return ;
		*i += 1;
		while (line[*i] != '\'' && line[*i])
		{
			*i += 1;
			*len += 1;
		}
		*len += 1;
	}
}

void	new_line_len_var(char *line, int *i, int *len, t_data *data)
{
	t_env	*search;
	char	*content;

	search = search_var(&line[*i], data);
	if (search != NULL)
	{
		content = cont_of_var(search->content);
		*len += ft_strlen(content);
	}
	while (ft_isalnum(line[*i]) && line[*i])
		*i += 1;
	if (search == NULL && (line[*i] == ' ' || line[*i] == '\0'))
		*len += 1;
}

void	new_line_len_varnum(char *line, int *i, int *len, t_data *data)
{
	if (line[*i + 1] == '?')
	{
		*len += num_len(data->last_error);
		*i += 1;
	}
	else
		*len += 1;
	*i += 1;
}

int	new_line_len(char *line, t_data *data)
{
	int		len;
	int		i;
	t_env	*search;
	char	*content;

	len = 0;
	i = 0;
	while (line[i])
	{
		new_line_len_base(line, &i, &len);
		if (line[i] == '$')
		{
			if (!ft_isalnum(line[i + 1]))
			{
				new_line_len_varnum(line, &i, &len, data);
				continue ;
			}
			i++;
			new_line_len_var(line, &i, &len, data);
			continue ;
		}
		if (line[i] != '\0')
			i++;
	}
	return (len);
}
