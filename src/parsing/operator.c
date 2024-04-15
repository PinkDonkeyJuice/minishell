#include "minishell.h"

int	is_operator(char *commande)
{
	int	i;

	i = 0;
	while (commande[i])
	{
		if (ft_strlen(commande) == 1)
		{
			if ((commande[i] == '>' && commande[i + 1] == '\0')
				|| (commande[i] == '<' && commande[i + 1] == '\0')
				|| (commande[i] == '|' && commande[i + 1] == '\0'))
				return (1);
		}
		if (ft_strlen(commande) == 2)
		{
			if ((commande[i] == '>' && commande[i + 1] == '>' && commande[i + 2] == '\0')
				|| (commande[i] == '<' && commande[i + 1] == '<' && commande[i + 2] == '\0')
				|| (commande[i] == '|' && commande[i + 1] == '|' && commande[i + 2] == '\0'))
				return (1);
		}
	}
	return (0);
}