#include "minishell.h"

bool	find_delim(char *line, char delim)
{
	while (*line)
	{
		if (*line == delim)
			return (true);
		line++;
	}
	return (false);
}

void	handle_operators(t_data *data, char *path_in, char *path_out, char delim, bool append)
{
	char	*line;

	if (append)
		data->fdout = open(path_out, O_RDWR, O_APPEND, O_CREAT, 0644);
	else
		data->fdout = open(path_out, O_RDWR, O_CREAT, 0644);
	if (data->fdin = open(path_in, O_RDONLY, 0644) == -1)
	{
		perror("Opening input file: ");
		exit(-1);
	}
	if (delim)
	{
		line = get_next_line(data->fdin);
		while(!find_delim(line, delim))
		{
			read(data->fdin, NULL, ft_strlen(line));
			line = get_next_line(data->fdin);
		}
	}
}
