/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:50:31 by marvin            #+#    #+#             */
/*   Updated: 2024/07/23 23:50:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void    send_message(int server_pid, char *str)
{
    int i;
    int bit;

    if (!*str)
    {
        write(1, "INVALID MESSAGE\n", 16);
        return ;
    }
    i = 0;
    while (str[i])
    {
        bit = 8;
        while (bit)
        {
            if ((str[i] >> bit) & 1)
                kill(server_pid, SIGUSR2);
            else
                kill(server_pid, SIGUSR1);
            bit--;
            usleep(50);
        }
        i++;
    }
}

int main(int ac, char **av)
{
    int pid;

    if (ac != 3)
    {
        write(1, "INVALID ARGUMENTS!\nUsage: ./client [SERVER_PID] [message]\n", 31);
        return (1);
    }
    pid = ft_atoi(av[1]);
    if (pid <= 0)
    {
        write(1, "INVALID PID\n", 12);
        return (1);
    }
    send_message(pid, av[2]);
    return (0);
}