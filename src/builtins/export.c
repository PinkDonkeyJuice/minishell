/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:46:31 by nchaize-          #+#    #+#             */
/*   Updated: 2024/04/19 11:55:12 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_export(char *line)
{
	int	i;
	int	j;
	char	*export;

	i = 0;
	j = 0;
	export = "export";
	while (line[i])
	{
		j = 0;
		while (line[i + j] == export[j])
		{
			if (line[i + j] == export[j] && export[j + 1] == '\0' 
				&& (line[i + j + 1] == ' ' || line[i + j + 1] == '\0'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}


void	exec_export(t_data *data)
{
	int	i;

	i = 1;
	while (data->command_list[i].command)
	{
		append_node(&(data->env_c), data->command_list[i].command);
		i++;
	}
}
