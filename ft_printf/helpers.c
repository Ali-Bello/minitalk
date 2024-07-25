/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 10:00:47 by aderraj           #+#    #+#             */
/*   Updated: 2023/12/27 16:15:41 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	specifier(char c)
{
	if (c == 'd' || c == 'i' || c == 'p' || c == 'c' || c == 'u'
		|| c == 'x' || c == 'X' || c == 's' || c == '%')
		return (1);
	return (0);
}

int	ft_count(unsigned long x, int y)
{
	int	count;

	count = 1;
	while (x >= (unsigned long)y)
	{
		x /= y;
		count++;
	}
	return (count);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(const char *str, int *i)
{
	long int	result;

	result = 0;
	if (str[*i] == '.')
		(*i)++;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		result = result * 10 + (str[*i] - '0');
		(*i)++;
	}
	return ((int)(result));
}
