#include "minishell.h"

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57)
		|| (c >= 65 && c <= 90)
		|| (c >= 97 && c <= 122))
		return (1);
	return (0);
}

int	num_len(int num)
{
	int	len;

	len = 1;
	while (num >= 10)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

int		len_tab(char **tab)
{
	int	count;

	count = 0;
	while (tab[count] != NULL)
		count++;
	return (count);
}

void	change_last_error(t_data *data, int i)
{
	data->last_error = i;
}