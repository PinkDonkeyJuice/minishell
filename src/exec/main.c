/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pinkdonkeyjuice <pinkdonkeyjuice@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:45:20 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/16 13:36:07 by pinkdonkeyj      ###   ########.fr       */
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
	read_input_main(&data);
	if (data.line == NULL)
		do_exit_end(&data);
}

size_t	commands_len(char **commands)
{
	size_t	i;

	i = 0;
	while (commands[i])
		i++;
	return (i);
}

void	ft_add_history(char *line)
{
	if (line && line[0])
		add_history(line);
}

void	read_input_main(t_data *data)
{
	data->line = readline("$> ");
	while (data->line != NULL)
	{
		ft_add_history(data->line);
		if (data->line[0] != '\0')
		{
			data->command_list = parse_line(data->line, data);
			data->n_commands = count_pipes(data->command_list);
			if (data->n_commands == 0)
			{
				free_command_list(data->command_list);
				data->line = readline("$> ");
				continue ;
			}
			data->commands = get_commands(data->command_list, 0);
			if (data->commands == NULL || data->command_list == NULL)
			{
				data->line = readline("$> ");
				continue ;
			}
			if (check_builtins_main(data) == 0 || data->n_commands != 1)
				exec_commands(data);
			if (data->heredoc_name)
				unlink(data->heredoc_name);
			free_all_comms(data);
		}
		data->line = readline("$> ");
	}
}
