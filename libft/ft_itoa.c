/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:07:27 by kez-zoub          #+#    #+#             */
/*   Updated: 2023/11/24 17:52:59 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	str_num_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		str_len;
	int		index;

	str_len = str_num_len(n) +1;
	str = (char *)malloc(str_len * sizeof(char));
	if (!str)
		return (NULL);
	index = str_len -1;
	str[index] = 0;
	index--;
	if (n < 0)
		str[0] = '-';
	if (n == 0)
		str[index] = '0';
	while (index >= 0 && n)
	{
		if (n % 10 >= 0)
			str[index] = n % 10 + '0';
		else
			str[index] = -(n % 10) + '0';
		n /= 10;
		index--;
	}
	return (str);
}
