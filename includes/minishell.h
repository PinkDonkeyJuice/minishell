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

typedef struct			s_mini
{
	int		fdin;
	int		fdout;
	int		pipin;
	int		pipout;
	char	**commands;
	int		parent;
}						t_mini;

size_t	ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
void	init_mini(t_mini data);

#endif