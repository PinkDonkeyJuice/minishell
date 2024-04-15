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
# include <stdbool.h>
# include <dirent.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <linux/limits.h>

# include "./get_next_line.h"

# define STDIN 0
# define STDOUT 1

# define TYPE_COMMAND 0
# define TYPE_PIPE 1
# define TYPE_OPERATOR 2

typedef struct		s_pipe
{
	size_t	id;
	int		p[2];
	struct s_pipe	*next;
}					t_pipe;

typedef struct		s_command
{
	char	*command;
	int		type;
}					t_command;

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
	t_command *command_list;
}						t_data;

size_t	ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
void	init_data(t_data *data);
void	exec(t_data *data, size_t i);
void	redir(t_data *data, t_pipe **pipe_list);
void	exec_commands(t_data *data);
void	generate_pipes(t_pipe **pipe_list, t_data *data);
char	*get_exec_path(char *line);
size_t	commands_len(char **commands);
void	create_pipe(size_t i, t_pipe **pipe_list);
t_pipe	*access_pipe(t_pipe **pipe_list, size_t i);
int		check_builtin(char *command);
void	close_all_pipes(t_data *data, t_pipe **pipe_list, size_t i, size_t j);
char	*get_next_line(int fd);

size_t	end_line(char *str);
char	*clean(char *str);
char	*ft_strdup(const char *s);
char	*append_stock(char *buffer, char *stock);
char	*ft_strstr(char *str, size_t start, size_t end);
char	*get_next_line(int fd);
char	*sub_line(char *stock);


//For parsing by Noam

int		check_builtins(t_data *data);
int	checker(char **line, t_data *data);
int		ft_isalnum(int c);
int		len_tab(char **tab);
void	change_last_error(t_data *data, int i);
int		num_len(int	num);

char	*ft_itoa(int n);

char	**get_args(char const *s, char c);

t_command	*parse_line(char *line, t_data *data);
int		checker(char **line, t_data *data);
t_command	*finish_parsing(t_command *parsed);

int		search_var(char *search, t_data *data);

char	*cont_of_var(char *var);
int		new_line_len(char *line, t_data *data);

char	**ft_split(char const *s, char c);

int		is_exit(char *line);
void	exec_exit(t_data *data);
void	do_exit(t_data *data);

int		is_echo(char *line);
void	exec_echo(t_data *data);

int		is_cd(char *line);
void	exec_cd(t_data *data);

int		is_pwd(char *line);
void	exec_pwd(void);

int		is_env(char *line);
void	exec_env(t_command *commande, char **env);
#endif