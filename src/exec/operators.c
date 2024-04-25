#include "minishell.h"

int    g_signal_handle;

void    here_doc_sigint(int sig)
{
    g_signal_handle = sig;
    rl_done = 1;
}

int    heredoc_signal_handler(void)
{
    struct sigaction    sa;

    ft_bzero(&sa, sizeof(sa));
    sa.sa_handler = here_doc_sigint;
    if (sigaction(SIGINT, &sa, NULL))
        return (-1);
    return (0);
}

char    *expand_line(char *line, t_data *data)
{
    int    i;

    i = 0;
    line = check_var(line, data);
    while (line[i])
    {
        if (line[i] < 0)
            line[i] *= -1;
        i++;
    }
    return (line);
}

void	read_input_heredoc(t_data *data)
{
	char	*line;

	line = NULL;
	while ((line = readline("$> here_doc: ")) != NULL)
	{
		if (ft_strcmp(line, data->delimiter) == 0)
		{
			close(data->fdin);
			data->fdin = open(data->heredoc_name, O_RDWR | O_CREAT, 0644);	
			return ;
		}
		if (g_signal_handle == SIGINT)
        {
            g_signal_handle = 0;
            data->last_error = 130;
            return (close(data->fdin), data->fdin = open(data->heredoc_name, O_RDWR | O_CREAT, 0644),
                (void) free(line));
        }
		line = expand_line(line, data);
		ft_putstr_fd(line, data->fdin);
		ft_putstr_fd("\n", data->fdin);
	}
}

void	here_doc(t_data *data)
{
	size_t i;
	bool	stop;
	char	*number;

	i = 0;
	stop = false;
 	heredoc_signal_handler();
	while (!stop)
	{
		number = ft_itoa(i);
		data->heredoc_name = ft_strjoin("./.heredoc_", number);
		if (access(data->heredoc_name, F_OK) == -1)
		{	
			if ((data->fdin = open(data->heredoc_name, O_RDWR | O_CREAT, 0644)) == -1)
			{}	//error();
			stop = true; 
		}
		i++;
	}
	read_input_heredoc(data);
}

void	handle_input_output(t_data *data)
{
	size_t i;
	char *command;

	i = -1;
	data->fdout = STDOUT_FILENO;
	data->fdin = STDIN_FILENO;
	while (data->command_list[++i].command)
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
				data->fdout = open(data->command_list[i + 1].command, O_RDWR | O_TRUNC | O_CREAT, 0644);
		}
	}
}
