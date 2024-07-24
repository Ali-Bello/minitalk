/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 10:05:10 by aderraj           #+#    #+#             */
/*   Updated: 2023/12/27 20:46:42 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	hex_hash(unsigned long x, t_format *specs)
{
	if (specs->flags[4] && x)
	{
		if (specs->specifier == 'x')
			ft_putnstr("0x", 2, specs->count);
		else if (specs->specifier == 'X')
			ft_putnstr("0X", 2, specs->count);
	}
}

static void	hex_minus(unsigned long x, char *base, t_format *specs)
{
	int	len;
	int	tmp;
	int	flag;

	len = ft_count(x, 16);
	tmp = *(specs->count);
	flag = specs->precision;
	hex_hash(x, specs);
	while (flag-- - len > 0)
		ft_putchar('0', specs->count);
	base_convert(x, specs, base);
	tmp = *(specs->count) - tmp;
	while (specs->width-- - tmp > 0)
		ft_putchar(' ', specs->count);
}

void	hex_zero(unsigned long x, char *base, t_format *specs)
{
	int		len;
	int		tmp;
	char	c;

	len = ft_count(x, 16);
	tmp = width_set(x, len, specs);
	c = ' ' * (specs->precision != -1) + '0' * (specs->precision == -1);
	specs->width -= 2 * (specs->flags[4] == 1 && x);
	if (c == '0')
		hex_hash(x, specs);
	while (specs->width-- - tmp > 0)
		ft_putchar(c, specs->count);
	if (c == ' ')
		hex_hash(x, specs);
	while (tmp-- > len)
		ft_putchar('0', specs->count);
	base_convert(x, specs, base);
}

static void	hex_default(unsigned long x, char *base, t_format *specs)
{
	int	len;
	int	tmp;

	len = ft_count(x, 16);
	tmp = width_set(x, len, specs);
	specs->width -= 2 * (specs->flags[4] == 1 && x);
	while (specs->width-- > tmp)
		ft_putchar(' ', specs->count);
	hex_hash(x, specs);
	while (tmp-- - len > 0)
		ft_putchar('0', specs->count);
	base_convert(x, specs, base);
}

void	hex_format(t_format *specs, va_list ap)
{
	unsigned long	x;
	char			*base;

	x = va_arg(ap, unsigned int);
	if (specs->specifier == 'X')
		base = "0123456789ABCDEF";
	else if (specs->specifier == 'x')
		base = "0123456789abcdef";
	if (specs->flags[0])
		hex_minus(x, base, specs);
	else if (specs->flags[1])
		hex_zero(x, base, specs);
	else
		hex_default(x, base, specs);
}
