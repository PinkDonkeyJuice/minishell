/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pinkdonkeyjuice <pinkdonkeyjuice@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:58:59 by nchaize-          #+#    #+#             */
/*   Updated: 2024/05/21 16:08:37 by pinkdonkeyj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_input_main_utils(t_data *data)
{
	char *name;
	
	if (check_builtins_main(data) == 0 || data->n_commands != 1)
		exec_commands(data);
	if (data->heredoc_name != NULL)
	{
		unlink(data->heredoc_name);
		free(data->heredoc_name);
		data->heredoc_name = NULL;
	}
}
