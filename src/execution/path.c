/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:46:53 by laoubaid          #+#    #+#             */
/*   Updated: 2024/07/26 16:19:47 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/execution.h"


char	*join_path_with_cmd(char *s1, char *s2)
{
	int		i;
	char	*join;

	i = 0;
	if (!s1 && !s2)
		return (0);
	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (0);
	if (s1)
		while (*s1)
			join[i++] = *s1++;
	if (s2)
	{
		while (*s2)
			join[i++] = *s2++;
	}
	join[i] = 0;
	return (join);
}

int	is_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	getpath(char **ev)
{
	int	i;

	i = 0;
	while (ev[i])
	{
		if (!(ft_strncmp(ev[i], "PATH=", 5)))
			return (i);
		i++;
	}
	return (-1);
}

int	path(char ***p, char *ev)
{
	char	**paths;
	char	*cmd;
	int		i;

	i = 0;
	paths = split_all(&ev[5], ':');
	while (paths[i])
	{
		cmd = join_path_with_cmd(paths[i], (*p)[0]);
		if (access(cmd, X_OK) == 0)
		{
			free((*p)[0]);
			(*p)[0] = cmd;
			ft_free(paths);
			return (0);
		}
		free(cmd);
		i++;
	}
	ft_free(paths);
	return (1);
}
