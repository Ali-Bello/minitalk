/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 11:49:20 by aderraj           #+#    #+#             */
/*   Updated: 2023/12/27 19:43:21 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c, int *count)
{
	write(1, &c, 1);
	(*count)++;
}

void	ft_putnstr(char *str, int n, int *count)
{
	int	i;

	i = 0;
	while (i < n && str[i])
		ft_putchar(str[i++], count);
}

void	base_convert(unsigned long int x, t_format *specs, char *base)
{
	if (!x && !specs->precision)
		return ;
	if (x >= 16)
		base_convert(x / 16, specs, base);
	ft_putchar(base[x % 16], specs->count);
}

void	ft_putnbr(long int x, t_format *specs)
{
	if (!x && !specs->precision)
		return ;
	else if (x > 9)
		ft_putnbr(x / 10, specs);
	ft_putchar(x % 10 + '0', specs->count);
}
