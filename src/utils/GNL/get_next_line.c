/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:29:41 by gyvergni          #+#    #+#             */
/*   Updated: 2024/01/31 15:00:47 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		find_end(char *buffer)
{
	int		i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (-1);
		i++;
	}
	return (0);
}

char	*sub_line(char *stock)
{
	char	*line;
	size_t	i_end;

	if (!stock)
		return (NULL);
	i_end = end_line(stock);
	if (i_end == 0 && stock[0] != '\n')
	{
		line = ft_strstr(stock, 0, ft_strlen(stock) - 1);
		return (line);
	}
	line = ft_strstr(stock, 0, i_end);
	return (line);
}

char	*update_stock(char *stock)
{
	char	*new_stock;
	size_t	i_end;

	if (!stock)
		return (NULL);
	i_end = end_line(stock);
	if ((i_end == 0 && stock[0] != '\n') || (i_end == ft_strlen(stock) - 1))
	{
		clean(stock);
		return (NULL);
	}
	new_stock = ft_strstr(stock, i_end + 1, ft_strlen(stock) - 1);
	if (!new_stock)
		return (clean(stock));
	clean(stock);
	return (new_stock);
}

char	*fill_line(char *stock, int fd)
{
	int		n_read;
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (clean(stock));
	n_read = read(fd, buffer, BUFFER_SIZE);
	while (n_read != 0)
	{
		if (n_read == -1)
		{
			clean(buffer);
			return (clean(stock));
		}
		buffer[n_read] = '\0';
		stock = append_stock(buffer, stock);
		if (!stock)
			return (clean(buffer));
		if (find_end(buffer) == -1)
			n_read = read(fd, buffer, BUFFER_SIZE);
	}
	clean(buffer);
	return (stock);
}

char	*get_next_line(int fd)
{
	static char		*stock;
	char			*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	stock = fill_line(stock, fd);
	if (!stock)
		return (NULL);
	line = sub_line(stock);
	if (!line)
	{
		stock = clean(stock);
		return (NULL);
	}
	stock = update_stock(stock);
	if (line[0] == '\0')
	{
		clean(line);
		return (NULL);
	}
	return (line);
}