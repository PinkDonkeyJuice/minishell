/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pinkdonkeyjuice <pinkdonkeyjuice@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:35:26 by pinkdonkeyj       #+#    #+#             */
/*   Updated: 2024/03/13 12:40:56 by pinkdonkeyj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_mini(t_mini data)
{
	int	pip[2];

	if (pipe(pip) == -1)
	{
		perror("In main: ");
		return (1);
	}
	data.pipin = &pip[0];
	data.pipout = &pip[1];
}