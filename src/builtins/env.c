
#include "minishell.h"

void	exec_env(t_data *data)
{
	t_env *print;

	print = data->env_c;
	while(print)
	{
		printf("%s\n", print->content);
		print = print->next;
	}
}
