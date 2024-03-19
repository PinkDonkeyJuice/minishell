#include "minishell.h"

void	exec(t_data *data, size_t i)
{
	char **cmd_split;
	char	*path;
	
	cmd_split = ft_split(data->commands[i], ' ');
	path = get_exec_path(data->commands[i]);
	if (!path)
		return ;
	execve(path, cmd_split, data->env);
}

void	redir(t_data *data, size_t i, t_pipe **pipe_list)
{
	pid_t	parent;
	int		p1;

	if (i != data->n_commands - 1)
		p1 = access_pipe(pipe_list, i)->p[1];
	parent = fork();
	if (parent == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (parent == 0)
	{
		if (i == 0 && data->n_commands != 1)
			dup2(p1, STDOUT_FILENO);
		else if (i == data->n_commands - 1 && data->n_commands != 1)
			dup2(access_pipe(pipe_list, i -1)->p[0], STDIN_FILENO);
		else if (data->n_commands != 1)
		{
			dup2(access_pipe(pipe_list, i - 1)->p[0], STDIN_FILENO);
			dup2(p1, STDOUT_FILENO);
		}
		close_pipes(data, pipe_list);
		exec(data, i);
	}
	else if (parent > 0)
	{
		waitpid(parent, NULL, 0); // Wait for child process to finish
	}
}

void	exec_commands(t_data *data)
{
	char	**commands;
	size_t	i;
	t_pipe	*pipe_list;

	commands = ft_split(data->line, '|');
	data->commands = commands;
	data->n_commands = commands_len(commands);
	pipe_list = NULL;
	generate_pipes(&pipe_list, data);
	i = 0;
	while (i < data->n_commands)
	{
		if (!check_builtin(commands[i]))
			redir(data, i, &pipe_list);
		i++;
	}
}
