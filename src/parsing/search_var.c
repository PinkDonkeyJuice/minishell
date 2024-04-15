
#include "minishell.h"

char	*cont_of_var(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=' && var[i + 1])
			return (&var[i + 1]);
		i++;
	}
	return (NULL);
}

int	search_var(char *search, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->env[i])
	{
		j = 0;
		while (data->env[i][j] == search[j] && search[j])
		{
			if ((search[j + 1] == '\0'
				|| !ft_isalnum(search[j + 1])) && data->env[i][j + 1] == '=')
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}