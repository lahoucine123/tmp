/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:11:20 by kez-zoub          #+#    #+#             */
/*   Updated: 2023/11/24 16:48:04 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	counter;
	size_t	tmp_counter;

	counter = 0;
	tmp_counter = 0;
	if (!*little)
		return ((char *)big);
	while (counter < len && *big)
	{
		if (*big == *little)
		{
			while (big[tmp_counter] == little[tmp_counter]
				&& little[tmp_counter]
				&& counter + tmp_counter < len)
				tmp_counter++;
			if (!little[tmp_counter])
				return ((char *)big);
			tmp_counter = 0;
		}
		big++;
		counter++;
	}
	return (NULL);
}
