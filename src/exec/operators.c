#include "minishell.h"

void	here_doc(t_data *data)
{
	char *line;
	size_t i;
	bool	stop;
	char 	*name;
	char	*number;

	i = 0;
	stop = false;
	while (!stop)
	{
		number = ft_itoa(i);
		name = ft_strjoin("./.heredoc_", number);
		if (access(name, F_OK) == -1)
		{	
			if ((data->fdin = open(name, O_RDWR | O_CREAT, 0644)) == -1)
			{}	//error();
			stop = true; 
		}
		i++;
	}
	while ((line = readline("$> here_doc: ")) != NULL)
	{
		if (ft_strcmp(line, data->delimiter) == 0)
			return ;
		ft_putstr_fd(line, data->fdin);
		ft_putstr_fd("\n", data->fdin);
	}
}

void	handle_input_output(t_data *data)
{
	size_t i;
	char *command;

	i = 0;
	data->fdout = STDOUT_FILENO;
	data->fdin = STDIN_FILENO;
	while (data->command_list[i].command)
	{
		command = data->command_list[i].command;
		if (data->command_list[i].type == TYPE_OPERATOR)
		{
			if (ft_strncmp(command, ">>", 2) == 0)
				data->fdout = open(data->command_list[i + 1].command, O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (ft_strncmp(command, "<", 2) == 0)
				if ((data->fdin = open(data->command_list[i + 1].command, O_RDONLY)) == -1)
					return ;
			if (ft_strncmp(command, "<<", 2) == 0)
			{
				data->delimiter = data->command_list[i + 1].command;
				here_doc(data);
			}
			if (ft_strncmp(command, ">", 2) == 0)
			{
				data->fdout = open(data->command_list[i + 1].command, O_RDWR | O_TRUNC | O_CREAT, 0644);
			}
		}
		i++;
	}
}
