/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjeon2 <qwer10897@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 03:44:10 by minjeon2          #+#    #+#             */
/*   Updated: 2023/07/26 22:13:41 by minjeon2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_demical(int inp)
{
	int	return_value;

	return_value = 0;
	if (inp == -2147483648)
	{
		write (1, "-2147483648", 11);
		return (11);
	}
	if (inp == 0)
		return (deal_zero_exception(0));
	if (inp < 0)
	{
		write(1, "-", 1);
		return_value++;
		inp *= -1;
	}
	ft_putnbr_fd(inp, 1);
	while (inp)
	{
		inp /= 10;
		return_value++;
	}
	return (return_value);
}

int	print_unsigned(int inp)
{
	int				return_value;
	unsigned int	unsigned_inp;

	return_value = 0;
	unsigned_inp = inp;
	if (unsigned_inp == 0)
	{
		write (1, "0", 1);
		return (1);
	}
	ft_putnbr_fd(unsigned_inp, 1);
	while (unsigned_inp != 0)
	{
		unsigned_inp /= 10;
		return_value++;
	}
	return (return_value);
}

int	print_char(char inp)
{
	write (1, &inp, 1);
	return (1);
}

int	print_va(char identifier, va_list ap)
{
	if (identifier == 'c')
		return (print_char(va_arg(ap, int)));
	else if (identifier == 'd' || identifier == 'i')
		return (print_demical(va_arg(ap, int)));
	else if (identifier == 's')
		return (ft_putstr_fd(va_arg(ap, char *), 1));
	else if (identifier == '%')
		return (ft_putstr_fd("%", 1));
	else if (identifier == 'u')
		return (print_unsigned(va_arg(ap, int)));
	else if (identifier == 'x')
		return (print_hex(va_arg(ap, unsigned int), 0));
	else if (identifier == 'X')
		return (print_hex(va_arg(ap, unsigned int), 1));
	else if (identifier == 'p')
		return (print_addr(va_arg(ap, unsigned long long)));
	return (0);
}
