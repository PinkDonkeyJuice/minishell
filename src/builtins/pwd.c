#include "minishell.h"

void	exec_pwd(void)
{
	char	buf[PATH_MAX];

	if (getcwd(buf, PATH_MAX))
		printf("%s\n", buf);
	else
		perror("Pwd: ");
}
