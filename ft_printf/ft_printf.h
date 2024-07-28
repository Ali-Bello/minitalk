/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 02:34:57 by aderraj           #+#    #+#             */
/*   Updated: 2024/07/28 04:20:23 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

typedef struct fomat
{
	int		flags[5];
	int		width;
	int		precision;
	char	specifier;
	int		sign;
	int		*count;
}			t_format;

int			ft_printf(const char *format, ...);

int			ft_scan(const char *ptr, va_list ap, int *count);
int			width_set(unsigned long x, int len, t_format *specs);

void		format(t_format *specs, va_list ap);
void		d_format(t_format *specs, va_list ap);
void		u_format(t_format *specs, va_list ap);
void		p_format(t_format *specs, va_list ap);
void		hex_format(t_format *specs, va_list ap);
void		s_format(t_format *specs, va_list ap);
void		c_format(char c, t_format *specs);
void		d_sign(t_format *specs);
void		d_zero(long x, int y, t_format *specs);
void		u_zero(long x, int y, t_format *specs);
void		hex_zero(unsigned long x, char *base, t_format *specs);
void		hex_hash(unsigned long x, t_format *specs);

int			specifier(char c);
int			ft_count(unsigned long x, int y);
int			ft_isdigit(int c);
int			ft_strlen(char *str);
int			ft_atoi(const char *str, int *i);

void		ft_putchar(char c, int *count);
void		ft_putnstr(char *str, int n, int *count);
void		ft_putnbr(long int x, t_format *specs);
void		base_convert(unsigned long int x, t_format *specs, char *base);

#endif
