/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:26:48 by gyvergni          #+#    #+#             */
/*   Updated: 2024/04/19 17:34:15 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	check_builtins_main(t_data *data)
{
	if (ft_strcmp(data->command_list[0].command, "exit"))
		exec_exit(data);
	if (ft_strcmp(data->command_list[0].command, "unset"))
		(exec_cd(data));
 	if (ft_strcmp(data->command_list[0].command, "export"))
		return (exec_export(data, false), 1);
	return (0);
}

int	check_builtins(t_data *data)
{
	if (ft_strcmp(data->commands[0], "cd"))
		return (exec_cd(data), 1);
	if (ft_strcmp(data->commands[0], "echo"))
		return (exec_echo(data), 1);
	if (ft_strcmp(data->commands[0], "pwd"))
		return (exec_pwd(), 1);
	if (ft_strcmp(data->commands[0], "export"))
		return (exec_export(data, true), 1);
	if (ft_strcmp(data->commands[0], "unset"))
		return (exec_unset(data), 1);
	if (ft_strcmp(data->commands[0], "env"))
		return (exec_env(data), 1);
	if (ft_strcmp(data->commands[0], "exit"))
		return (exec_exit(data), 1);
	return (0);
}