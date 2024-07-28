/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:19:36 by marvin            #+#    #+#             */
/*   Updated: 2024/07/28 04:40:46 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	construct_char(int sig, char *c, int *bits_no)
{
	if (sig == SIGUSR1)
	{
		*c = (*c << 1) | 0;
		(*bits_no)++;
	}
	else if (sig == SIGUSR2)
	{
		*c = (*c << 1) | 1;
		(*bits_no)++;
	}
}

void	handle_signals(int sig, siginfo_t *info, void *context)
{
	static int	bits_no;
	static int	sender_pid;
	static char	c;

	(void)context;
	if (info && sender_pid == 0)
		sender_pid = info->si_pid;
	else if (info && sender_pid != info->si_pid)
	{
		sender_pid = 0;
		bits_no = 0;
		c = 0;
	}
	construct_char(sig, &c, &bits_no);
	if (bits_no == 8)
	{
		if (!c)
			kill(sender_pid, SIGUSR2);
		else
			write(1, &c, 1);
		bits_no = 0;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signals;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	ft_printf(BOLD BLUE" ____  _____ ______     _______ ____  \n"
		"/ ___|| ____|  _ \\ \\   / / ____|  _ \\ \n"
		"\\___ \\|  _| | |_)|\\ \\ / /|  _| | |_) |\n"
		" ___) | |___|  _ < \\ V / | |___|  _ < \n"
		"|____/|_____|_| \\_\\ \\_/  |_____|_| \\_\\\n"RESET);
	ft_printf(CYAN"\n	SERVER PID : "BOLD GREEN"%d\n"RESET, getpid());
	ft_printf("\n");
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
