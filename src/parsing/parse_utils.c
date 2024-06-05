/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:04:51 by nchaize-          #+#    #+#             */
/*   Updated: 2024/06/05 15:14:21 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57)
		|| (c >= 65 && c <= 90)
		|| (c >= 97 && c <= 122))
		return (1);
	return (0);
}

int	num_len(int num)
{
	int	len;

	len = 1;
	while (num >= 10)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

int	len_tab(char **tab)
{
	int	count;

	count = 0;
	while (tab[count] != NULL)
		count++;
	return (count);
}

int	last_check(t_command *parsed)
{
	int	i;

	i = 0;
	while (parsed[i].command)
	{
		if (parsed[i].type == TYPE_OPERATOR && parsed[i + 1].command == NULL)
			return (printf("minishell: Syntax error\n"), 0);
		i++;
	}
	return (1);
}
