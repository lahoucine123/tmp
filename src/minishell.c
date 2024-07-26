/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:32:02 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/07/26 19:02:39 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/execution.h"


char	*env_fetch(char *var)
{
	while (*var && *var != '=')
		var++;
	if (*var == '=' && *(var + 1))
		return (*var = 0, var + 1);
	return (NULL);
}

t_env	*env_init(char **env)
{
	t_env	*head;
	t_env	*tmp;

	tmp = malloc(sizeof(t_env));
	tmp->name = *env;
	tmp->value = env_fetch(*env);
	head = tmp;
	env++;
	while(*env)
	{
		tmp->next = malloc(sizeof(t_env));
		tmp->name = *env;
		tmp->value = env_fetch(*env);
		tmp = tmp->next;
		env++;
	}
	tmp->next = NULL;
	return (head);
}

char	**env_dup(char **env)
{
	char	**new_env;
	int i;
	
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

t_param *param_init(char **env)
{
	t_param *param;

	param = malloc(sizeof(t_param));
	param->env_arr = env_dup(env);
	param->env = env_init(env);
	return (param);
}

int	main(int argc, char **argv, char **env)
{
	char	*buffer;
	t_param *param;
	int		syntax_error;
	int		exit_status;

	syntax_error = 0;
	param = param_init(env);
	shell_signals();
	while (1)
	{
		if (syntax_error)
			buffer = readline("\e[31m➜  \e[36mMiniShell\e[0m ");
		else
			buffer = readline("\e[32m➜  \e[36mMiniShell\e[0m ");
		syntax_error = parser(buffer, &(param->ast));
		// print_ast(param->ast);
		exit_status = execute(param);
		printf("exit code: %d\n", exit_status);
		clean_ast(param->ast);
	}
	return (0);
}
