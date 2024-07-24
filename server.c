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

void    handle_sigusr1(int signum)
{

}

void    handle_sigusr2(int signum)
{

}

int main()
{
    struct sigaction sa;
    struct sigaction sa1;

    sa.sa_handler = handle_sigusr1;
    sa.sa_handler = handle_sigusr2;

    ft_printf("SERVER PID : %d\n", getpid());
}