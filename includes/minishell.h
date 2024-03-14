#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>

# define STDIN 0
# define STDOUT 1


typedef struct			s_data
{
	int		fdin;
	int		fdout;
	int		last_error;
	int		pipin;
	int		pipout;
	size_t	n_commands;
	char	*line;
	char	**commands;
	int		parent;
	char	**env;
}						t_data;

size_t	ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
void	init_data(t_data *data);

#endif