/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:42:18 by laoubaid          #+#    #+#             */
/*   Updated: 2024/08/01 01:15:05 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/execution.h"

char	*env_fetch(char *var, t_env *tmp)
{
	while (*var && *var != '=')
		var++;
	if (*var == '=')
	{
		*var = 0;
		tmp->print_flag = 1;
	}
	else
	{
		tmp->print_flag = 0;
		return (NULL);
	}
	return (var + 1);
}

t_env	*env_init(char **env)
{
	t_env	*head;
	t_env	*tmp;
	char	*dup;

	tmp = malloc(sizeof(t_env));
	dup = ft_strdup(*env);
	tmp->name = dup;
	tmp->value = env_fetch(dup, tmp);
	head = tmp;
	env++;
	while(*env)
	{
		tmp->next = malloc(sizeof(t_env));      /////need cleaning
		dup = ft_strdup(*env);
		tmp->next->name = dup;
		tmp->next->value = env_fetch(dup, tmp->next);
		tmp = tmp->next;
		env++;
	}
	tmp->next = NULL;
	return (head);
}

char	**env_default(void)
{
	char	**env;

	env = malloc(sizeof(char *) * 5);
	env[0] = strjoin_optclean("PWD=", getcwd(NULL, 0), 2);
	env[1] = ft_strdup("SHLVL=2");
	env[2] = ft_strdup("_=./minishell");
	env[3] = ft_strdup("OLDPWD");
	env[4] = NULL;
	return (env);
}

char	**env_dup(char **env)
{
	char	**new_env;
	int		i;
	
	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

t_param	*param_init(char **env)
{
	t_param	*param;

	param = malloc(sizeof(t_param));
	if (!*env)
		param->env_arr = env_default();
	else
		param->env_arr = env_dup(env);
	param->env = env_init(param->env_arr);
	return (param);
}
