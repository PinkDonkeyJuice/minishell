#include "minishell.h"

int	is_pwd(char *line)
{
	int		i;
	int		j;
	char	*pwd;

	i = 0;
	j = 0;
	pwd = "pwd";
	while (line[i])
	{
		j = 0;
		while (line[i + j] == pwd[j])
		{
			if (line[i + j] == pwd[j] && pwd[j + 1] == '\0'
				&& (line[i + j + 1] == ' ' || line[i + j + 1] == '\0'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	exec_pwd(void)
{
	char	buf[PATH_MAX];

	if (getcwd(buf, PATH_MAX))
		printf("%s\n", buf);
	/*securiser pwd*/
}