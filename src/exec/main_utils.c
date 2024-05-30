/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:58:59 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/27 13:54:13 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_input_main_utils(t_data *data)
{
	if (is_builtin_main(data) == 1 && data->n_commands == 1)
		check_builtins_main(data);
	else
		exec_commands(data);
}

void	init_commands(t_data *data)
{
	data->command_list = parse_line(data->line, data);
	data->n_commands = count_pipes(data->command_list);
}

void	no_commands(t_data *data)
{
	free_command_list(data->command_list);
	data->line = readline("$> ");
}

size_t	commands_len(char **commands)
{
	size_t	i;

	i = 0;
	while (commands[i])
		i++;
	return (i);
}