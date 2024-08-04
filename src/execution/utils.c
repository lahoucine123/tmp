/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:01:39 by laoubaid          #+#    #+#             */
/*   Updated: 2024/08/01 01:20:57 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/execution.h"

char	*strjoin_optclean(char *s1, char *s2, int flag)
{
	int		i;
	char	*join;
	char	*tmp;

	i = 0;
	tmp = s1;
	if (!s1 && !s2)
		return (0);
	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (0);
	if (s1)
		while (*s1)
			join[i++] = *s1++;
	s1 = s2;
	if (s2)
		while (*s2)
			join[i++] = *s2++;
	if (flag == 1 || flag == 3)
		free(tmp);
	if (flag == 2 || flag == 3)
		free(s1);
	return (join[i] = 0, join);
}
