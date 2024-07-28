/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:19:36 by marvin            #+#    #+#             */
/*   Updated: 2024/07/23 22:19:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

void printCharBits(char c)
{
    for (int i = 7; i >= 0; i--)
    {
        putchar((c & (1 << i)) ? '1' : '0');
    }
    putchar('\n');
}

void printBits(int num)
{
    unsigned int size = sizeof(int) * 8; // Calculate the number of bits in an integer
    unsigned int maxPow = 1 << (size - 1); // Find the maximum power of 2 value
    for(unsigned int i = 0; i < size; i++)
    {
        // Print 0 or 1 depending on the value of the current bit
        printf("%u", num & maxPow ? 1 : 0);
        num = num << 1; // Shift the number by 1 to check the next bit
    }
    printf("\n");
}

void    handle_signals(int sig, siginfo_t *info, void *context)
{
    static int      bits_no;
    static int      sender_pid;
    static char     c;

    (void)context;
    if (info)
    {
        if (sender_pid == 0)
            sender_pid = info->si_pid;
        else if (sender_pid != info->si_pid)
        {
            sender_pid = 0;
            bits_no = 0;
            c = 0;
        }
    }
    if (sig == SIGUSR1)
    {
        c = (c << 1) | 0;
        bits_no++;
    }
    else if (sig == SIGUSR2)
    {
        c = (c << 1) | 1;
        bits_no++;
    }
    if (bits_no == 8 && !c)
        kill(sender_pid, SIGUSR2);
    else if (bits_no == 8)
    {
        write(1, &c, 1);
        bits_no = 0;
        c = 0;
    }
}

int main()
{
    struct  sigaction    sa;

    sa.sa_sigaction = handle_signals;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    ft_printf("SERVER PID : %d\n", getpid());
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    while (1)
        pause();
    return (0);
}