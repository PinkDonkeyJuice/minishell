/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_parse_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:13:57 by nchaize-          #+#    #+#             */
/*   Updated: 2024/06/05 15:09:42 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	finish_check_var(char *line, char *new_line, t_parse *c, int *h)
{
	if (line[c->i] == '<')
		is_heredoc(line, new_line, c, h);
	if (line[c->i] != ' ' && line[c->i] != '<' && *h == 1)
		*h = 0;
	if (line[c->i])
		i_plusplus_j_plusplus(line, &(c->i), &(c->j));
}

void	init_parse_struct(t_parse *c)
{
	c->i = 0;
	c->j = 0;
}
