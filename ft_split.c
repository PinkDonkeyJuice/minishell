/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyvergni <gyvergni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:03:30 by gyvergni          #+#    #+#             */
/*   Updated: 2024/03/12 13:05:42 by gyvergni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	count_words(char const *str, char c)
{
	int	count;
	int	i;
	int	new;

	new = 1;
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			new = 1;
		else if (str[i] != c && new == 1)
		{
			count++;
			new = 0;
		}
		i++;
	}
	return (count);
}

char	*assign(char const *s, char c, int i)
{
	int		i_word;
	int		len;
	char	*word;

	i_word = 0;
	len = 0;
	while (s[i + len] && s[i + len] != c)
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (word == NULL)
		return (NULL);
	while (s[i] && s[i] != c)
	{
		word[i_word] = s[i];
		i++;
		i_word++;
	}
	word[i_word] = '\0';
	return (word);
}

void	freetable(char **split, int i_split)
{
	while (i_split >= 0)
	{
		free(split[i_split]);
		i_split--;
	}
	free(split);
}

char	**fill_split(char const *s, char c, char **split)
{
	int	i;
	int	new;
	int	i_split;

	i = -1;
	new = 1;
	i_split = 0;
	while (s[++i])
	{
		if (s[i] == c)
			new = 1;
		if (s[i] != c && new == 1)
		{
			split[i_split] = assign(s, c, i);
			if (split[i_split] == NULL)
			{
				freetable(split, i_split);
				return (NULL);
			}
			new = 0;
			i_split++;
		}
	}
	split[i_split] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (s == NULL)
		return (NULL);
	split = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (split == NULL)
		return (NULL);
	split = fill_split(s, c, split);
	return (split);
}
