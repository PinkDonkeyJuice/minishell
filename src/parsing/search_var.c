/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pinkdonkeyjuice <pinkdonkeyjuice@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:57:18 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/16 18:34:59 by pinkdonkeyj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cont_of_var(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=' && var[i + 1])
			return (&var[i + 1]);
		i++;
	}
	return (NULL);
}

t_env	*search_var(char *namevar, t_data *data)
{
	int		i;
	t_env	*search;

	i = 0;
	search = data->env_c;
	while (search)
	{
		i = 0;
		while (search->content[i] == namevar[i] && namevar[i])
		{
			if ((!ft_isalnum(namevar[i + 1]) && namevar[i + 1] != '_')
				&& (search->content[i + 1] == '='
					|| search->content[i + 1] == '\0'))
				return (search);
			i++;
		}
		search = search->next;
	}
	return (NULL);
}
