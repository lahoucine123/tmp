/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 19:53:45 by kez-zoub          #+#    #+#             */
/*   Updated: 2023/11/25 00:26:09 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem_alloc;
	size_t	max;

	if (!nmemb || !size)
		return (malloc(0));
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	max = nmemb * size;
	mem_alloc = malloc(max);
	if (!mem_alloc)
		return (NULL);
	ft_bzero(mem_alloc, max);
	return (mem_alloc);
}
