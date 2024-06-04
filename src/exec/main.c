/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:45:20 by gyvergni          #+#    #+#             */
/*   Updated: 2024/06/04 15:44:33 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void) argc;
	(void) argv;
	rl_event_hook = void_event;
	init_data(&data);
	init_env(env, &data);
	data.env = env;
	signal_handler();
	data.line = readline("$> ");
	read_input_main(&data);
	if (data.line == NULL)
		do_exit_end(&data);
}

void	ft_add_history(char *line)
{
	if (line && line[0])
		add_history(line);
}

int	out_of_bound(char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (0);
	while (line[i] != '\0')
	{
		if (line[i] < 0)
			return (1);
		i++;
	}
	return (0);
}

void	reset_input_main(t_data *data)
{
	if (data->fdin != STDIN_FILENO && data->fdin != -1)
		close(data->fdin);
	if (data->fdout != STDOUT_FILENO && data->fdout != -1)
		close(data->fdout);
	data->line = readline("$> ");
}

void	read_input_main(t_data *data)
{
	if (out_of_bound(data->line))
		exit(1);
	while (data->line != NULL)
	{
		ft_add_history(data->line);
		if (data->line[0] != '\0')
		{
			init_commands(data);
			if (data->n_commands == 0 || data->command_list[0].command == NULL
				|| data->command_list[0].command[0] == '\0')
			{
				no_commands(data);
				continue ;
			}
			data->commands = get_commands(data->command_list, 0);
			if (data->commands == NULL || data->command_list == NULL)
			{
				data->line = readline("$> ");
				continue ;
			}
			read_input_main_utils(data);
			free_all_comms(data);
		}
		reset_input_main(data);
	}
}
