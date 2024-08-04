/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_suite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:03:59 by laoubaid          #+#    #+#             */
/*   Updated: 2024/08/02 11:25:51 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/execution.h"

char	**recreate_env(t_env *env_list, char **env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env_list;
	while (tmp)
	{
		if (tmp->print_flag)
			i++;
		tmp = tmp->next;
	}
	env = malloc(sizeof(char *) * (i + 1));
	tmp = env_list;
	i = 0;
	while (tmp)
	{
		if (tmp->print_flag)
		{
			env[i] = strjoin_optclean("=", tmp->value, 0);
			env[i] = strjoin_optclean(tmp->name, env[i], 2);
			i++;
		}
		tmp = tmp->next;
	}
	return (env[i] = NULL, env);
}

int	env_edit(t_param *param, char *find, char *value)
{
	t_env	*tmp;

	tmp = param->env;
	while (tmp)
	{
		if (!ft_strncmp(find, tmp->name, ft_strlen(find)))
		{
			free(tmp->name);
			tmp->name = strjoin_optclean(find, "=", 0);
			tmp->name = strjoin_optclean(tmp->name, value, 3);
			tmp->value = env_fetch(tmp->name, tmp);
			param->env_arr = recreate_env(param->env, NULL);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	print_variables(t_param *param)
{
	t_env	*tmp;

	tmp = param->env;
	while (tmp)
	{
		if (ft_strncmp("_", tmp->name, 2))
		{
			write(1, tmp->name, ft_strlen(tmp->name));
			if (tmp->value)
			{
				write(1, "=\"", 2);
				write(1, tmp->value, ft_strlen(tmp->value));
				write(1, "\"", 1);
			}
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
}

int checkifvalid(char *str, int *idx)
{
	char	*tmp;

	tmp = str;
		
	if (!str)
		return ((*idx)++, 0);
	if (!*str || *str == '=')
	{
		write(2, tmp, ft_strlen(tmp));
		write(2, ": not a valid identifier\n", 25);
		return ((*idx)++, 0);
	}
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) || ft_isdigit(str[0]))
		{
			write(2, tmp, ft_strlen(tmp));
			write(2, ": not a valid identifier\n", 25);
			return ((*idx)++, 0);
		}
		str++;
	}
	return (1);
}

int checkifexist(char *str, t_env *env, int *idx)
{
	int		i;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		i = ft_strlen(tmp->name);
		if (!ft_strncmp(str, tmp->name, i))
		{
			if (str[i] == '=')
			{
				free(tmp->name);
				tmp->name = ft_strdup(str);
				tmp->value = env_fetch(tmp->name, tmp);
				(*idx)++;
				return (1);
			}
			if (!str[i])
				return ((*idx)++, 1);
		}
		tmp = tmp->next;
	}
	return (0);
}
