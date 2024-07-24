/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 12:27:55 by aderraj           #+#    #+#             */
/*   Updated: 2023/12/27 20:47:57 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	width_set(unsigned long x, int len, t_format *specs)
{
	int	tmp;

	tmp = len * (specs->precision <= len)
		+ specs->precision * (specs->precision > len);
	if (!x && !specs->precision)
		tmp = 0;
	if (!specs->sign && (specs->flags[2] || specs->flags[3]))
		specs->width--;
	return (tmp);
}

void	d_sign(t_format *specs)
{
	if (specs->flags[3])
	{
		if (specs->sign)
			ft_putchar('-', specs->count);
		else
			ft_putchar('+', specs->count);
	}
	else if (specs->flags[2])
	{
		if (specs->sign)
			ft_putchar('-', specs->count);
		else
			ft_putchar(' ', specs->count);
	}
	else if (specs->sign)
		ft_putchar('-', specs->count);
}
