/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pinkdonkeyjuice <pinkdonkeyjuice@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:26:48 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/15 01:17:40 by pinkdonkeyj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins_main(t_data *data)
{
	if (data->commands == NULL || data->commands[0] == NULL)
		return (0);
	if (!ft_strcmp(data->commands[0], "exit"))
		return (exec_exit(data), 1);
	if (!ft_strcmp(data->commands[0], "unset"))
		return (exec_unset(data), 1);
	if (!ft_strcmp(data->commands[0], "export"))
		return (exec_export(data), 1);
	if (!ft_strcmp(data->commands[0], "cd"))
		return (exec_cd(data), 1);
	return (0);
}

int	is_builtin(t_data *data)
{
	if (data->commands == NULL || data->commands[0] == NULL)
		return (0);
	if (!ft_strcmp(data->commands[0], "cd"))
		return (1);
	if (!ft_strcmp(data->commands[0], "echo"))
		return (1);
	if (!ft_strcmp(data->commands[0], "pwd"))
		return (1);
	if (!ft_strcmp(data->commands[0], "export"))
		return (1);
	if (!ft_strcmp(data->commands[0], "unset"))
		return (1);
	if (!ft_strcmp(data->commands[0], "env"))
		return (1);
	if (!ft_strcmp(data->commands[0], "exit"))
		return (1);
	return (0);
}

int	check_builtins(t_data *data)
{
	if (!ft_strcmp(data->commands[0], "cd"))
		return (exec_cd(data), 1);
	if (!ft_strcmp(data->commands[0], "echo"))
		return (exec_echo(data), 1);
	if (!ft_strcmp(data->commands[0], "pwd"))
		return (exec_pwd(data), 1);
	if (!ft_strcmp(data->commands[0], "export"))
		return (exec_export(data), 1);
	if (!ft_strcmp(data->commands[0], "unset"))
		return (exec_unset(data), 1);
	if (!ft_strcmp(data->commands[0], "env"))
		return (exec_env(data), 1);
	if (!ft_strcmp(data->commands[0], "exit"))
		return (exec_exit(data), 1);
	return (0);
}
