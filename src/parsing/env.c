
#include "minishell.h"

int	is_env(char *line)
{
	int	i;
	int	j;
	char	*env;

	i = 0;
	j = 0;
	env = "env";
	while (line[i])
	{
		j = 0;
		while (line[i + j] == env[j])
		{
			if (line[i + j] == env[j] && env[j + 1] == '\0' 
				&& (line[i + j + 1] == ' ' || line[i + j + 1] == '\0'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	exec_env(t_command *command, char **env)
{
	int	i;

	i = 0;
	(void) command;
	while(env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}