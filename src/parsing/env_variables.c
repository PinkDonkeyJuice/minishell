/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:01:21 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/06 15:02:31 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		s_len;
	char		*sub;

	sub = NULL;
	s_len = ft_strlen((char *)s) - start;
	if (start >= (unsigned int)ft_strlen((char *)s))
	{
		sub = malloc(sizeof(char));
		if (sub == NULL)
			return (sub);
		sub[0] = '\0';
		return (sub);
	}
	if (len <= s_len)
		sub = malloc(sizeof(char) * (len + 1));
	else if (len > s_len)
		sub = malloc(sizeof(char) * (s_len + 1));
	if (sub == NULL)
		return (sub);
	i = -1;
	while (s[start + ++i] && i < len)
		sub[i] = ((char *)s)[start + i];
	sub[i] = '\0';
	return (sub);
}

