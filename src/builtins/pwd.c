/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pinkdonkeyjuice <pinkdonkeyjuice@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:42:26 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/05 19:59:39 by pinkdonkeyj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pwd(t_data *data)
{
	char	buf[PATH_MAX];

	if (data->commands[1] != NULL)
	{
		data->last_error = 1;
		printf("Error: too many arguments to function call\n");
		free_commands(data->commands);
		free_command_list(data->command_list);
		return ;
	}
	if (getcwd(buf, PATH_MAX))
		printf("%s\n", buf);
	else
		perror("Pwd: ");
	free_all_comms(data);
}
