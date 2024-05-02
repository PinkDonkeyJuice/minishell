/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:45:20 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/02 14:38:03 by gyvergni         ###   ########.fr       */
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
	data.last_error = 0;
	signal_handler();
	read_input_main(&data);
	if (data.line == NULL)
		do_exit(&data);
}

char	*get_exec_path(char *command)
{
	int		i;
	char	**paths;
	char	*try_path;

	paths = ft_split(getenv("PATH"), ':');
	try_path = NULL;
	i = 0;
	if (paths && command)
	{
		while (paths[i])
		{
			try_path = ft_strdup(paths[i]);
			if (try_path != NULL)
				try_path = ft_strjoin(try_path, "/");
			if (try_path != NULL)
				try_path = ft_strjoin(try_path, command);
			if (!try_path)
				return (NULL);
			if (access(try_path, X_OK) == 0)
				return (try_path);
			i++;
		}
	}
	return (command);
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
			if (data->command_list == NULL)
			{
				data->line = readline("$> ");
				continue ;
			}
			data->n_commands = count_pipes(data->command_list);
			data->commands = get_commands(data->command_list, 0);
			if (check_builtins_main(data) == 0 || data->n_commands != 1)
				exec_commands(data);
			if (data->heredoc_name)
				unlink(data->heredoc_name);
			print_commands(data->commands);
			free_all_comms(data);
		}
		data->line = readline("$> ");
	}
}
