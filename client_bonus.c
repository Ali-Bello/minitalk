/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:50:31 by marvin            #+#    #+#             */
/*   Updated: 2024/07/28 04:45:34 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		g_server_pid;

void	send_final_sig(void)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		kill(g_server_pid, SIGUSR1);
		usleep(400);
		i++;
	}
}

void	send_message(char *str)
{
	int	i;
	int	bit;

	if (!*str)
	{
		write(1, "INVALID MESSAGE\n", 16);
		return ;
	}
	i = 0;
	while (str[i])
	{
		bit = 7;
		while (bit >= 0)
		{
			if ((str[i] >> bit) & 1)
				kill(g_server_pid, SIGUSR2);
			else
				kill(g_server_pid, SIGUSR1);
			bit--;
			usleep(400);
		}
		i++;
	}
	send_final_sig();
}

int	check_pid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9') && str[i] != '-'
			&& str[i] != '+')
			return (-1);
		i++;
	}
	return (ft_atoi_r(str));
}

void	handle_sig(int signum)
{
	if (signum == SIGINT)
	{
		send_final_sig();
		exit(0);
	}
	else if (signum == SIGUSR2)
		ft_printf(GREEN"message recieved by the server succesfully!\n"\
		RESET);
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sig;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	if (ac != 3)
	{
		ft_printf(BOLD RED "ERROR : INVALID ARGUMENTS!\n"RESET);
		ft_printf(MAGENTA"Usage: ./client [SERVER_PID] [message]\n"RESET);
		return (1);
	}
	g_server_pid = check_pid(av[1]);
	if (g_server_pid <= 0)
	{
		ft_printf(BOLD RED"ERROR : INVALID PID\n"RESET);
		return (1);
	}
	send_message(av[2]);
	return (0);
}
