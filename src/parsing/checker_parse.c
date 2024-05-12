/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:48:32 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/06 15:02:43 by gyvergni         ###   ########.fr       */
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
	/*if (line[*i] == '\"' && g == 0)
	{
		g = 1;
		*len += 1;
		*i += 1;
	}
	if (line[*i] == '\"' && g == 1)
	{
		g = 0;
		*len += 1;
		if (line[*i + 1])
			*i += 1;
	}*/
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
			if (new_line[*j] == '\"' || new_line[*j] == '\''
				|| new_line[*j] == '|' || new_line[*j] == '<'
				|| new_line[*j] == '>')
				new_line[*j] *= -1;
			content++;
			*j += 1;
		}
	}
	while ((ft_isalnum(data->line[*i]) || data->line[*i] == '_') && data->line[*i])
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

void	i_plusplus_j_plusplus(char *line, int *i, int *j)
{
	if (line[*i] != '\0')
	{
		*i += 1;
		*j += 1;
	}
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

t_command	*finish_parsing(t_command *parsed)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (parsed[i].command)
	{
		j = 0;
		while (parsed[i].command[j])
		{
			if (parsed[i].command[j] < 0)
			{
				if (parsed[i].command[j] == -32)
					parsed[i].command[j] = 0;
				parsed[i].command[j] *= -1;
			}
			j++;
		}
		i++;
	}
	return (parsed);
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
