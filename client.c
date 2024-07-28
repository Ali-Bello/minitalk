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

int server_pid;

void    send_final_sig(void)
{
    int i;

    i = 0;
    while (i < 8)
    {
        kill(server_pid, SIGUSR1);
        usleep(250);
        i++;
    }
}

void    send_message(char *str)
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
        bit = 7;
        while (bit >= 0)
        {
            if ((str[i] >> bit) & 1)
                kill(server_pid, SIGUSR2);
            else
                kill(server_pid, SIGUSR1);
            bit--;
            usleep(500);
        }
        i++;
    }
    send_final_sig();
}

int check_pid(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return (-1);
        i++;
    }
    i = 0;
    return (ft_atoi(str, &i));
}

void    handle_sig(int signum)
{
    if (signum == SIGINT)
    {
        send_final_sig();
        exit(0);
    }
    else if (signum == SIGUSR2)
        write(1, "message recieved by the server succesfully!\n", 44);
}

int main(int ac, char **av)
{
    struct sigaction    sa;

    sa.sa_handler = handle_sig;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    if (ac != 3)
    {
        write(1, "INVALID ARGUMENTS!\nUsage: ./client [SERVER_PID] [message]\n", 31);
        return (1);
    }
    server_pid = check_pid(av[1]);
    if (server_pid <= 0)
    {
        write(1, "INVALID PID\n", 12);
        return (1);
    }
    send_message(av[2]);
    return (0);
}
