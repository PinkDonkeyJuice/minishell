/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:45:20 by gyvergni          #+#    #+#             */
/*   Updated: 2024/04/23 15:49:22 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "stdlib.h"
#include "minishell.h"

int		void_event(void)
{
	return (0);
}

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
	return (command);
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

void    handle_sigint(int sig)
{
    (void) sig;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int    signal_handler(void)
{
    struct sigaction    sa;

    signal(SIGQUIT, SIG_IGN);
    ft_bzero(&sa, sizeof(sa));
    sa.sa_handler = handle_sigint;
    if (sigaction(SIGINT, &sa, NULL))
        return (-1);
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
	rl_event_hook = void_event;
	init_data(&data);
	init_env(env, &data);
	data.env = env;
	data.last_error = 0;
	signal_handler();
	while ((data.line = readline("$> ")) != NULL)
	{
		ft_add_history(data.line);
		if (data.line[0] != '\0')
		{
			data.command_list = parse_line(data.line, &data);
			if (data.command_list == NULL)
				continue ;
			data.n_commands = count_pipes(data.command_list);
			data.commands = get_commands(data.command_list, 0);
			printf("Command 0 is %s\n", data.commands[0]);
  			print_commands(data.command_list);
			print_type(data.command_list);
			if (check_builtins_main(&data) == 0 || data.n_commands != 1)
				exec_commands(&data);
			if (data.heredoc_name)
				unlink(data.heredoc_name);
		}
	}
	if (data.line == NULL)
		do_exit(&data);
}
