/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:57:18 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/23 13:34:34 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cont_of_var(char *var)
{
	int	i;

	i = 0;
	if (!var)
		return (NULL);
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
	if (namevar == NULL)
		return (NULL);
	search = data->env_c;
	while (search)
	{
		i = 0;
		while (search->content != NULL && search->content[i] == namevar[i] && namevar[i])
		{
			if ((!ft_isalnum(namevar[i + 1]) && namevar[i + 1] != '_')
				&& (search->content[i + 1] == '\0'
					|| search->content[i + 1] == '='))
				return (search);
			i++;
		}
		search = search->next;
	}
	return (NULL);
}
