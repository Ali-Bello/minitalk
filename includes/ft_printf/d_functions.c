/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_functions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 09:49:56 by aderraj           #+#    #+#             */
/*   Updated: 2023/12/27 20:44:41 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	d_minus(long x, int d, t_format *specs)
{
	int	tmp;
	int	flag;

	flag = specs->precision;
	tmp = *(specs->count);
	if (specs->sign)
		specs->width++;
	d_sign(specs);
	while (flag-- > d)
		ft_putchar('0', specs->count);
	ft_putnbr(x, specs);
	tmp = *(specs->count) - tmp;
	while (specs->width-- - tmp > 0)
		ft_putchar(' ', specs->count);
}

void	d_zero(long x, int y, t_format *specs)
{
	int		tmp;
	int		flag;
	char	c;

	flag = (specs->precision != -1) + 0 * (specs->precision == -1);
	tmp = width_set(x, y, specs);
	if (!flag)
		d_sign(specs);
	c = ' ' * (specs->precision != -1) + '0' * (specs->precision == -1);
	while (specs->width-- > tmp)
		ft_putchar(c, specs->count);
	if (flag)
		d_sign(specs);
	while (tmp-- > y)
		ft_putchar('0', specs->count);
	ft_putnbr(x, specs);
}

static void	d_precision(long x, int y, t_format *specs)
{
	int	tmp;
	int	flag;

	tmp = width_set(x, y, specs);
	flag = specs->precision;
	while (specs->width-- > tmp)
		ft_putchar(' ', specs->count);
	d_sign(specs);
	while (flag-- > y)
		ft_putchar('0', specs->count);
	ft_putnbr(x, specs);
}

static void	d_default(long x, int len, t_format *specs)
{
	if (!specs->sign && (specs->flags[2] || specs->flags[3]))
		specs->width--;
	while (specs->width-- > len)
		ft_putchar(' ', specs->count);
	d_sign(specs);
	ft_putnbr(x, specs);
}

void	d_format(t_format *specs, va_list ap)
{
	long	x;
	int		y;

	x = va_arg(ap, int);
	if (x < 0)
	{
		specs->sign = 1;
		x *= -1;
		specs->width--;
	}
	y = ft_count(x, 10);
	if (specs->flags[0])
		d_minus(x, y, specs);
	else if (specs->flags[1])
		d_zero(x, y, specs);
	else if (specs->precision > -1)
		d_precision(x, y, specs);
	else
		d_default(x, y, specs);
}
