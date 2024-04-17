/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:06:28 by gyvergni          #+#    #+#             */
/*   Updated: 2024/04/16 11:40:38 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	c;

	c = 0;
	while (str[c] != '\0')
	{
		c++;
	}
	return (c);
}

char	*ft_strdup(const char *s)
{
	char		*dup;
	size_t		i;
	size_t		len;

	i = 0;
	len = ft_strlen((char *)s);
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		len1;
	size_t		len2;
	int			i;
	int			j;
	char		*sj;

	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	sj = malloc(sizeof(char) * (len1 + len2 + 1));
	if (sj == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		sj[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		sj[i + j] = s2[j];
		j++;
	}
	sj[i + j] = '\0';
	return (sj);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}


void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}


char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;

	if (*little == '\0')
	{
		return ((char *)big);
	}
	i = 0;
	j = 0;
	while (big[i] && i < len)
	{
		if (big[i] == little[j])
		{
			while (big[i] && little[j] && ((j + i) < len)
				&& big[i + j] == little[j])
				j++;
			if (little[j] == '\0')
				return ((char *)big + i);
			j = 0;
		}
		i++;
	}
	return (NULL);
}
