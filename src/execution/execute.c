/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:07:43 by laoubaid          #+#    #+#             */
/*   Updated: 2024/07/26 19:09:14 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/execution.h"

int	command_execution(t_cmd *cmdr, char **env)
{
	char **cmd;
    int exit_status;

	cmd = cmdr->simple_cmd;
    if (!check_if_path(cmd[0]))
        path(&cmd, env[getpath(env)]);
	if (!fork())
	{
		redirecte(cmdr);
        exit_status = execution_errors(cmd[0]);
        if (exit_status)
            exit(exit_status);
		execve(cmd[0], cmd, env);
		if (cmd[0])
			write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, ": command not found", 19);
		write(2, "\n", 1);
		exit(127);
	}
	wait(&exit_status);
    if (WIFEXITED(exit_status))
        return (WEXITSTATUS(exit_status));
    return (-1);
}


int    handle_operations(t_param *param)
{
    int exit_status;
    t_ast *tmp;

    exit_status = 0;
    tmp = param->ast->right;
    if (param->ast->type == OR)
    {
        param->ast = param->ast->left;
        if (execute(param) != 0)
        {
            param->ast = tmp;
            exit_status = execute(param);
        }
    }
    else
    {
        param->ast = param->ast->left;
        if (execute(param) == 0)
        {
            param->ast = tmp;
            exit_status = execute(param);
        }
    }
    return (exit_status);
}

int subshell(t_param *param)
{
    int pid;
    int exit_status;

    pid = fork();
    if (!pid)
    {
        if (param->ast->cmd != NULL)
            redirecte(param->ast->cmd);
        param->ast = param->ast->left;
        exit(execute(param));
    }
    wait(&exit_status);
    if (WIFEXITED(exit_status))
        return (WEXITSTATUS(exit_status));
    return (-1);
}

t_pipe    *pipeline(t_ast *ast)
{
    t_pipe  *pip;
    t_pipe  *tmp;

    if (ast->left->type == PIPE)
        pip = pipeline(ast->left);
    else
    {
        pip = malloc(sizeof(t_pipe));
        pip->cmd = ast->left->cmd;
        pip->next = NULL;
    }
    tmp = pip;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = malloc(sizeof(t_pipe));
    tmp = tmp->next;
    tmp->cmd = ast->right->cmd;
    tmp->next = NULL;
    return (pip);
}

int    execute(t_param *param)
{
    int exit_status;
    
    if (param->ast->type == OR || param->ast->type == AND)
        exit_status = handle_operations(param);
    else if (param->ast->type == PIPE)
        exit_status = handle_pipe(pipeline(param->ast), param->env_arr);
    else if (param->ast->type == LPAREN)
        exit_status = subshell(param);
    else
        exit_status = command_execution(param->ast->cmd, param->env_arr);
    return (exit_status);
}
