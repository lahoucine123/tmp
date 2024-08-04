/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:33:33 by laoubaid          #+#    #+#             */
/*   Updated: 2024/08/04 22:10:14 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/execution.h"

int	ft_echo(char **cmd)
{
	int	flag;
	int	i;

	i = 1;
	flag = 0;
	if (cmd[1])
	{
		if (!ft_strncmp("-n", cmd[1], 3))
		{
			flag = 1;
			i++;
		}
	}
	while (cmd[i])
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	return (0);
}

int	ft_exit(char **cmd)
{
	int	i;

	i = 0;
	if (cmd[1])
	{
		while (cmd[1][i])
		{
			if (!ft_isdigit(cmd[1][i]))
			{
				write(2, "numeric argument required\n", 26);
				// clean the programme
				exit(2);
			}
			i++;
		}
		if (!cmd[2]) // clean here as well
			exit(ft_atoi(cmd[1]));
		else
		{
			write(2, "exit: too many arguments\n", 25);
			return (1);
		}
	}
	// also clean this area
	exit(1);
}

int ft_env(t_param *param)
{
	char	**tmp;

	tmp = param->env_arr;

	while (*tmp)
	{
		write(1, *tmp, ft_strlen(*tmp));
		write(1, "\n", 1);
		tmp++;
	}
	return (0);
}

int ft_export(t_param *param , char **cmd)
{
	int		i;
	t_env	*tmp;

	i = 1;
	if (!cmd[1])
		print_variables(param);
	tmp = param->env;
	while (tmp->next)
		tmp = tmp->next;
	while (cmd[i])
	{
		if (!checkifvalid(cmd[i], &i) || checkifexist(cmd[i], param->env, &i))
			continue ;
		tmp->next = malloc(sizeof(t_env));
		tmp = tmp->next;
		tmp->next = NULL;
		tmp->name = ft_strdup(cmd[i]);
		tmp->value = env_fetch(tmp->name, tmp);
		i++;
	}
	param->env_arr = recreate_env(param->env, NULL);
	return (0);
}

int	builtins(t_param *param, t_cmd *cmd)
{
	int		fd[2];
	int		exit_status;

	exit_status = -1;
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	redirecte(cmd, 0, 0, 0);
	if (!ft_strncmp(cmd->simple_cmd[0], "cd", 2))
		exit_status = ft_cd(param);									//done V
	else if (!ft_strncmp(cmd->simple_cmd[0], "echo", 4))
		exit_status = ft_echo(cmd->simple_cmd);						//done V
	else if (!ft_strncmp(cmd->simple_cmd[0], "pwd", 3))
		exit_status = ft_pwd(param);								//done V
	else if (!ft_strncmp(cmd->simple_cmd[0], "export", 6))
		exit_status = ft_export(param, cmd->simple_cmd);			//done (almost) v
	else if (!ft_strncmp(cmd->simple_cmd[0], "unset", 5))
		exit_status = ft_unset(param, cmd->simple_cmd);				//done V
	else if (!ft_strncmp(cmd->simple_cmd[0], "env", 3))
		exit_status = ft_env(param);								//done V
	else if (!ft_strncmp(cmd->simple_cmd[0], "exit", 4))
		exit_status = ft_exit(cmd->simple_cmd);						//done V
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	return (close(fd[0]), close(fd[1]), exit_status);
	// return (exit_status);
}
