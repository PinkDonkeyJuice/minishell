/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:30:17 by gyvergni          #+#    #+#             */
/*   Updated: 2023/12/14 14:30:19 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

char	*append_stock(char *buffer, char *stock)
{
	size_t	i;
	size_t	j;
	char	*join;

	if (!stock)
	{
		stock = malloc(sizeof(char));
		if (!stock)
			return (NULL);
		stock[0] = '\0';
	}
	if (!buffer)
		return (stock);
	join = malloc(ft_strlen(buffer) + ft_strlen(stock) + 1);
	if (!join)
		return (clean(stock));
	i = -1;
	while (stock[++i])
		join[i] = stock[i];
	j = -1;
	while (buffer[++j])
		join[i + j] = buffer[j];
	join[i + j] = '\0';
	clean(stock);
	return (join);
}

char	*ft_strstr(char *str, size_t start, size_t end)
{
	char	*new_str;
	size_t	i;

	new_str = malloc(end - start + 2);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < end - start + 1)
	{
		new_str[i] = str[start + i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*clean(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
	return (NULL);
}

size_t	end_line(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}
