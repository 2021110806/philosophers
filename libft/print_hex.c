/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjeon2 <qwer10897@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 03:46:34 by minjeon2          #+#    #+#             */
/*   Updated: 2023/07/26 22:13:06 by minjeon2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	deal_zero_exception(int is_addr)
{
	if (is_addr)
	{
		write(1, "0x0", 3);
		return (3);
	}
	write(1, "0", 1);
	return (1);
}

int	calc_hex(unsigned long long remained, int is_uppercase)
{
	if (remained <= 9)
		return (48);
	else
	{
		if (is_uppercase)
			return (55);
		else
			return (87);
	}
}

int	print_hex(unsigned long long inp, int is_uppercase)
{
	char	arr[16];
	int		idx;
	int		remained;
	int		return_value;

	idx = 15;
	return_value = 0;
	if (inp == 0)
		return (deal_zero_exception(0));
	while (inp)
	{
		remained = inp % 16;
		arr[idx] = remained + calc_hex(remained, is_uppercase);
		idx--;
		inp /= 16;
	}
	idx++;
	while (idx < 16)
	{
		write(1, &arr[idx], 1);
		idx++;
		return_value++;
	}
	return (return_value);
}

int	print_addr(unsigned long long inp)
{
	char					arr[16];
	int						idx;
	unsigned long long		remained;
	int						return_value;

	idx = 15;
	return_value = 2;
	if (inp == 0)
		return (deal_zero_exception(1));
	while (inp)
	{
		remained = inp % 16;
		arr[idx] = remained + calc_hex(remained, 0);
		idx--;
		inp /= 16;
	}
	write(1, "0x", 2);
	idx++;
	while (idx < 16)
	{
		write(1, &arr[idx], 1);
		idx++;
		return_value++;
	}
	return (return_value);
}
