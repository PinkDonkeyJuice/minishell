/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:58:59 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/22 13:55:07 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_input_main_utils(t_data *data)
{
	char	*name;

	if (check_builtins_main(data) == 0 || data->n_commands != 1)
		exec_commands(data);
	if (data->heredoc_name != NULL)
	{
		unlink(data->heredoc_name);
		free(data->heredoc_name);
		data->heredoc_name = NULL;
	}
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
