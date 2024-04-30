/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:02:36 by nchaize-          #+#    #+#             */
/*   Updated: 2024/04/25 14:03:03 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	number_len(unsigned int n)
{
	int	len;

	len = 1;
	while (n >= 10)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static char	*itoa_p(int n, char *num, int i)
{
	num[i] = '\0';
	i--;
	while (i >= 0)
	{
		num[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	return (num);
}

static char	*itoa_n(unsigned int un, char *num, int i)
{
	num[i] = '\0';
	i--;
	while (i > 0)
	{
		num[i] = un % 10 + '0';
		un = un / 10;
		i--;
	}
	num[i] = '-';
	return (num);
}

char	*ft_itoa(int n)
{
	char			*num;
	int				i;
	unsigned int	un;

	if (n >= 0)
	{
		i = number_len(n);
		num = malloc(sizeof(char) * (i + 1));
		if (!num)
			return (NULL);
		itoa_p(n, num, i);
		return (num);
	}
	if (n < 0)
	{
		un = -n;
		i = number_len(un) + 1;
		num = malloc(sizeof(char) * (i + 1));
		if (!num)
			return (NULL);
		itoa_n(un, num, i);
		return (num);
	}
	return (NULL);
}
