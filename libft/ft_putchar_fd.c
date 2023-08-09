/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjeon2 <minjeon2@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:05:18 by minjeon2          #+#    #+#             */
/*   Updated: 2023/03/21 21:32:46 by minjeon2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "unistd.h"

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}
