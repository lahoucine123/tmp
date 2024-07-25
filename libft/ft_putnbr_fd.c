/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:09:54 by kez-zoub          #+#    #+#             */
/*   Updated: 2023/11/23 16:43:22 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	num;

	if (fd < 0)
		return ;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (n == -2147483648)
		{
			ft_putchar_fd('2', fd);
			n %= 1000000000;
		}
		n *= -1;
	}
	if (n < 10)
	{
		num = n + '0';
		ft_putchar_fd(num, fd);
	}
	else
	{
		ft_putnbr_fd(n / 10, fd);
		num = n % 10 + '0';
		ft_putchar_fd(num, fd);
	}
}
