/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeminian <aeminian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 21:02:17 by aeminian          #+#    #+#             */
/*   Updated: 2024/07/22 15:57:08 by aeminian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_irc(int signum);

int	handler(void)
{
	return (0);
}

void	signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &ft_irc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	rl_catch_signals = 0;
	rl_event_hook = &handler;
}

void	ft_irc(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		rl_done = 42;
	}
}