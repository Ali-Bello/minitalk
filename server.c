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

int bits_count;
char    c;

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

void    handle_sigusr1()
{
    c = (c << 1) | 0;
    bits_count++;
    if (bits_count == 8)
    {
        // printCharBits(c);
        write(1, &c, 1);
        bits_count = 0;
        c = 0;
    }
}

void    handle_sigusr2()
{
    c = (c << 1) | 1;
    bits_count++;
    if (bits_count == 8)
    {
        // printCharBits(c);
        write(1, &c, 1);
        bits_count = 0;
        c = 0;
    }
}

int main()
{
    struct  sigaction    sa;
    struct  sigaction    sa1;

    sa.sa_handler = handle_sigusr1;
    sigemptyset(&sa.sa_mask);
    sa1.sa_handler = handle_sigusr2;
    sigemptyset(&sa1.sa_mask);
    c = 0;
    bits_count = 0;
    printBits(bits_count);
    ft_printf("SERVER PID : %d\n", getpid());
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa1, NULL);
    while (1)
        pause();
    return (0);
}