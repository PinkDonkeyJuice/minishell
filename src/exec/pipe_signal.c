/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:43:44 by gyvergni          #+#    #+#             */
/*   Updated: 2024/05/28 12:01:22 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_pipe_signal(int signum)
{
	(void)signum;
}

void	hook_pipe_signal(void)
{
	struct sigaction	sig;

	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_RESTART;
	sig.sa_handler = handle_pipe_signal;
	if (sigaction(SIGPIPE, &sig, NULL) == -1)
		perror("sigaction");
}
