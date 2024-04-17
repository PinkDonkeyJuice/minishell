/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:45:20 by gyvergni          #+#    #+#             */
/*   Updated: 2024/04/17 12:08:39 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "stdlib.h"
#include "minishell.h"

char	*get_exec_path(char *command)
{
	int		i;
	char 	**paths;
	char	*try_path;

	paths = ft_split(getenv("PATH"), ':');
	//ft_putstr_fd(command, 1);
	i = 0;
	if (paths && command)
	{
		while (paths[i])
		{
			if ((try_path = ft_strdup(paths[i])) == NULL)
				return (NULL);
			if ((try_path = ft_strjoin(try_path, "/")) == NULL)
				return (NULL);
			if ((try_path = ft_strjoin(try_path, command)) == NULL)
				return (NULL);
			if (access(try_path, X_OK) == 0)
			{
				//ft_putstr_fd(try_path, 1);
				return (try_path);
			}
			i++;
		}
	}
	return (NULL);
}

size_t	commands_len(char **commands)
{
	size_t i;

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

void	handle(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
	}
}

int	check_builtins_main(t_data *data)
{
	if (is_exit(data->command_list[0].command))
		exec_exit(data);
	if (is_cd(data->command_list[0].command))
		(exec_cd(data));
	return (0);
}

int	check_builtins(t_data *data)
{
	if (is_cd(data->commands[0]))
		return (exec_cd(data), 1);
	if (is_echo(data->commands[0]))
		return (exec_echo(data), 1);
	if (is_pwd(data->commands[0]))
		return (exec_pwd(), 1);
/*	if (is_export(line))
		return (exec_export(), 1);
	if (is_unset(line))
		return (exec_unset(), 1); */
/*	if (is_env(data->command_list[0].command))
		return (exec_env(data->command_list, data->env), 1);*/
	if (is_exit(data->commands[0]))
		return (exec_exit(data), 1);
	return (0);
}

void	print_commands(t_command *commands)
{
	int	i;

	i = 0;
	while (commands[i].command)
	{
		ft_putstr_fd(commands[i].command, 1);
		write(1, "\n", 1);
		i++;
	}
}

void	print_type(t_command *command_list)
{
	int i;

	i = 0;
	while (command_list[i].command != NULL)
	{
		printf("Type of command is %d\n", command_list[i].type);
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void) argc;
	(void) argv;
	init_data(&data);
	init_env(env, &data);
	data.env = env;
	data.last_error = 0;
	signal(SIGINT, handle);
	signal(SIGQUIT, SIG_IGN);
	while ((data.line = readline("$> ")) != NULL)
	{
		ft_add_history(data.line);
		if (data.line[0] != '\0')
		{
			data.command_list = parse_line(data.line, &data);
			if (data.command_list == NULL)
				continue ;
			data.n_commands = count_pipes(data.command_list);
			check_builtins_main(&data);
  			print_commands(data.command_list);
		/*	print_type(data.command_list); */
			exec_commands(&data);
		}
	}
	if (data.line == NULL)
		do_exit(&data);
}
