/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:48:32 by nchaize-          #+#    #+#             */
/*   Updated: 2024/04/19 15:28:20 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_closed_quotes(char *line)
{
	int	i;
	int	g1;
	int	g2;

	i = 0;
	g1 = 0;
	g2 = 0;
	while (line[i])
	{
		if (line[i] == '\"' && g1 == 0 && g2 == 0)
		{
			g1 = 1;
			i++;
		}
		if (line[i] == '\'' && g2 == 0 && g1 == 0)
		{
			g2 = 1;
			i++;
		}
		if (line[i] == '\'' && g2 == 1 && g1 == 0)
			g2 = 0;
		if (line[i] == '\"' && g1 == 1 && g2 == 0)
			g1 = 0; 
		i++;
	}
	if (g1 == 0 && g2 == 0)
		return (1);
	else
		return (0);
}

int	check_operator(char *line)
{
	int	i;
	int	o;

	i = 0;
	o = 0;
	while (line[i])
	{
		if (line[i] == '\"')
		{
			i++;
			while (line[i] != '\"')
				i++;
		}
		if (line[i] == '\'')
		{
			i++;
			while (line[i] != '\'')
				i++;
		}
		if (line[i] == '>' && line[i + 1] && o == 0)
		{
			o = 1;
			i++;
			if (line[i] == '>')
				i++;
		}
		if (line[i] == '<' && line[i + 1] && o == 0)
		{
			o = 1;
			i++;
			if (line[i] == '<')
				i++;
		}
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

int		new_line_len(char *line, t_data *data)
{
	int	len;
	int	i;
	t_env	*search;
	char *content;

	len = 0;
	i = 0;
	while(line[i])
	{
		if (line[i] != '$' && line[i] != '\'')
			len++;
		if (line[i] == '\'')
		{
			len++;
			i++;
			while (line[i] != '\'')
			{
				i++;
				len++;
			}
		}
		if (line[i] == '$')
		{
			if(!ft_isalnum(line[i + 1]))
			{
				if (line[i + 1] == '?')
				{
					len += num_len(data->last_error); 
					i++;
				}
				i++;
				continue ;
			}
			i++;
			search = search_var(&line[i], data);
			if (search != NULL)
			{
				content = cont_of_var(search->content);
				len += ft_strlen(content);
			}
			while (ft_isalnum(line[i]) && line[i])
				i++;
			if (search == NULL && (line[i] == ' ' || line[i] == '\0'))
				len++;
			continue ;
		}
		i++;
	}
	return (len);
}


void	check_var_sq(char *line, char *new_line, int *i, int *j)
{
	new_line[*j] = line[*i];
	*i += 1;
	*j += 1;
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

void	check_var_dq(char *line, char *new_line, int *i, int *j)
{
	new_line[*j] = line[*i];
	*i += 1;
	*j += 1;
	while (line[*i] != '\"' && line[*i] && line[*i] != '$')
	{
		new_line[*j] = line[*i];
		*i += 1;
		*j += 1;
	}
	if (line[*i] == '$')
		return ;
	new_line[*j] = line[*i];
	*i += 1;
	*j += 1; 
	return ;
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

char	*check_var(char *line, t_data *data)
{
	char	*new_line;
	char	*content;
	t_env	*search;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_line = malloc(sizeof(char) * (new_line_len(line, data) + 1));
	if (!new_line)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '\'')
			check_var_sq(line, new_line, &i, &j);
		else if (line[i] == '\"')
		{
			check_var_dq(line, new_line, &i, &j);
			continue ;
		}
		else
		{
			if (line[i] == '$')
			{
				if (!ft_isalnum(line[i + 1]))
				{
					not_an_env_var(data, new_line, &i, &j);
					continue ;
				}
				i++;
				search = search_var(&line[i], data);
				if (search != NULL)
				{
					content = cont_of_var(search->content);
					while (*content)
					{
						new_line[j] = *content;
						if (new_line[j] == '\"' || new_line[j] == '\''
							|| new_line[j] == '|' || new_line[j] == '<'
							|| new_line[j] == '>')
							new_line[j] *= -1;
						content++;
						j++;
					}
				}
				while (ft_isalnum(line[i]) && line[i])
					i++;
				if (search == NULL && (line[i] == ' ' || line[i] == '\0'))
				{
					new_line[j] = -32;
					j++;
				}
				continue ;
			}
			new_line[j] = line[i];
		}
		if (line[i] != '\'')
		{
			i++;
			j++;
		}
	}
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
