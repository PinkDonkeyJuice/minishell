/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaize- <@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:45:15 by gyvergni          #+#    #+#             */
/*   Updated: 2024/06/05 10:34:10 by nchaize-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal_handle;

int	void_event(void)
{
	return (0);
}

void	handle_sigint(int sig)
{
	(void) sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	signal_handler(void)
{
	struct sigaction	sa;

	hook_pipe_signal();
	signal(SIGQUIT, SIG_IGN);
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = handle_sigint;
	if (sigaction(SIGINT, &sa, NULL))
		return (-1);
	return (0);
}

void	here_doc_sigint(int sig)
{
	g_signal_handle = sig;
	rl_done = 1;
}

int	heredoc_signal_handler(t_data *data)
{
	struct sigaction	sa;

	(void) data;
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = here_doc_sigint;
	if (sigaction(SIGINT, &sa, NULL))
		return (-1);
	return (0);
}
