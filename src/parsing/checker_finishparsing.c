/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_finishparsing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:39:34 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/14 17:39:34 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
