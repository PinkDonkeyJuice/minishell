/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:46:06 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/02 13:00:26 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <errno.h>

# define STDIN 0
# define STDOUT 1

# define TYPE_COMMAND 0
# define TYPE_PIPE 1
# define TYPE_OPERATOR 2

typedef struct s_env
{
	char			*content;
	struct s_env	*next;
	struct s_env	*previous;
}				t_env;

typedef struct s_pipe
{
	size_t			id;
	int				p[2];
	struct s_pipe	*next;
}					t_pipe;

typedef struct s_command
{
	char	*command;
	int		type;
}				t_command;

typedef struct s_data
{
	int			fdin;
	int			fdout;
	char		*heredoc_name;
	char		*delimiter;
	int			last_error;
	size_t		n_commands;
	char		*line;
	char		**commands;
	int			parent;
	t_command	*command_list;
	t_env		*env_c;
	char		**env;
	t_pipe		**pipe_list;
}				t_data;

size_t		ft_strlen(const char *str);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char const *s1, char const *s2);
void		init_data(t_data *data);
void		exec(t_data *data, size_t i);
void		redir(t_data *data, t_pipe **pipe_list);
void		exec_commands(t_data *data);
void		generate_pipes(t_pipe **pipe_list, t_data *data);
char		*get_exec_path(char *line);
size_t		commands_len(char **commands);
void		create_pipe(size_t i, t_pipe **pipe_list);
t_pipe		*access_pipe(t_pipe **pipe_list, size_t i);
void		close_pipes(t_data *data, t_pipe **pipe_list, size_t i, size_t j);

size_t		end_line(char *str);
char		*clean(char *str);
char		*ft_strdup(const char *s);
char		*append_stock(char *buffer, char *stock);
char		*ft_strstr(char *str, size_t start, size_t end);
char		*sub_line(char *stock);
void		ft_putstr_fd(char *s, int fd);

void	close_safe( t_data *data, int fd);
void	free_all(t_data *data);


int			ft_strncmp(const char *s1, const char *s2, size_t n);

char		**get_commands(t_command *cl, size_t i);

size_t		count_pipes(t_command *command_list);

char		*ft_strnstr(const char *big, const char *little, size_t len);

void		handle_input_output(t_data *data);

int			ft_strcmp(const char *s1, const char *s2);

void		exec_unset(t_data *data);

void	handle_commands(t_data *data, t_pipe **pipe_list);

void	parent_process(t_data *data, t_pipe **pipe_list);

void	child_process(t_data *data, t_pipe **pipe_list, size_t i);

int	void_event(void);

void	here_doc_sigint(int sig);

int	heredoc_signal_handler(void);

void	ft_putchar_fd(char c, int fd);

/*Built-	ins*/

int			check_builtins_main(t_data *data);

int			check_builtins(t_data *data);
//For pa	rsing by Noam

int			checker(char **line, t_data *data);
int			ft_isalnum(int c);
int			len_tab(char **tab);
void		change_last_error(t_data *data, int i);
int			num_len(int num);

char		*ft_itoa(int n);

char		**get_args(char const *s, char c);

t_command	*parse_line(char *line, t_data *data);
int			checker(char **line, t_data *data);
t_command	*finish_parsing(t_command *parsed);

t_env		*search_var(char *namevar, t_data *data);

char		*cont_of_var(char *var);
int			new_line_len(char *line, t_data *data);

char		**ft_split(char const *s, char c);

int			is_exit(char *line);
void		exec_exit(t_data *data);
void		do_exit(t_data *data);

t_env		*find_last_node(t_env *env);
void		append_node(t_env **env, char *env_var);
void		init_env(char **env, t_data *data);

int			is_echo(char *line);
void		exec_echo(t_data *data);

int			is_cd(char *line);
void		exec_cd(t_data *data);

int			is_pwd(char *line);
void		exec_pwd(void);

int			is_env(char *line);
void		exec_env(t_data *data);

int			is_export(char *line);
void		exec_export(t_data *data);

void		ft_bzero(void *s, size_t n);

int			signal_handler(void);

char		*check_var(char *line, t_data *data);

void	error(t_data *data, char *err_msg);

char	**free_commands(char **commands);

void	free_pipes(t_pipe **pipe_list);

void	free_env(t_env	*env);

void	free_command_list(t_command *command_list);


#endif