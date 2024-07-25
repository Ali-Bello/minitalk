/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_functions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 12:25:10 by aderraj           #+#    #+#             */
/*   Updated: 2023/12/26 13:03:21 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	p_minus(t_format *specs, void *ptr, int len)
{
	int	tmp;

	tmp = *(specs->count);
	ft_putnstr("0x", 2, specs->count);
	while (specs->precision-- - len + 2 > 0)
		ft_putchar('0', specs->count);
	base_convert((unsigned long)ptr, specs, "0123456789abcdef");
	tmp = *(specs->count) - tmp;
	while (specs->width-- - tmp > 0)
		ft_putchar(' ', specs->count);
}

static void	p_zero(t_format *specs, void *ptr, int len)
{
	ft_putnstr("0x", 2, specs->count);
	while (specs->width-- - len > 0)
		ft_putchar('0', specs->count);
	while (specs->precision-- - len + 2 > 0)
		ft_putchar('0', specs->count);
	base_convert((unsigned long)ptr, specs, "0123456789abcdef");
}

static void	p_default(t_format *specs, void *ptr, int len)
{
	int	tmp;

	tmp = specs->precision * (specs->precision > len) + len
		* (specs->precision <= len);
	while (specs->width-- - tmp > 0)
		ft_putchar(' ', specs->count);
	ft_putnstr("0x", 2, specs->count);
	while (specs->precision-- - len + 2 > 0)
		ft_putchar('0', specs->count);
	base_convert((unsigned long)ptr, specs, "0123456789abcdef");
}

void	p_format(t_format *specs, va_list ap)
{
	void	*ptr;
	int		len;

	ptr = va_arg(ap, void *);
	if (!ptr)
		len = 3;
	else
		len = ft_count((unsigned long)ptr, 16) + 2;
	if (specs->flags[0])
		p_minus(specs, ptr, len);
	else if (specs->flags[1])
		p_zero(specs, ptr, len);
	else
		p_default(specs, ptr, len);
}
