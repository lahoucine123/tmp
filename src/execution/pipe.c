/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 01:28:54 by laoubaid          #+#    #+#             */
/*   Updated: 2024/07/25 01:36:06 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/execution.h"

int count_pipe(t_pipe *pip)
{
    int i;

    i = 0;
    while (pip)
    {
        i++;
        pip = pip->next;
    }
    return (i);
}

int	**allocate_for_pipe(int n)
{
	int	i;
	int	**fd;

	i = 0;
	fd = malloc(sizeof(int *) * n);
	while (i < n)
	{
		fd[i] = malloc(2 * sizeof(int));
		i++;
	}
	return (fd);
}

int	handle_cmd(t_pipe *pip, int *fdin, int *fdout, char **env)
{
    int exit_status;

    if (fdin)
    {
        close(fdin[1]);
        dup2(fdin[0], STDIN_FILENO);
        close(fdin[0]);
    }
    if (fdout)
    {
        close(fdout[0]);
        dup2(fdout[1], STDOUT_FILENO);
        close(fdout[1]);
    }
    if (!check_if_path(pip->cmd->simple_cmd[0]))
        path(&(pip->cmd->simple_cmd), env[getpath(env)]);
    redirecte(pip->cmd);
    exit_status = execution_errors(pip->cmd->simple_cmd[0]);
    if (exit_status)
        exit(exit_status);
    execve(pip->cmd->simple_cmd[0], pip->cmd->simple_cmd, env);
    if (pip->cmd->simple_cmd[0])
        write(2, pip->cmd->simple_cmd[0], ft_strlen(pip->cmd->simple_cmd[0]));
    write(2, ": command not found", 19);
    write(2, "\n", 1);
    exit(127);
}

int	ftclose(int **fd, int n)
{
	while (n - 2 >= 0)
	{
		close(fd[n - 2][0]);
		close(fd[n - 2][1]);
		n--;
	}
	return (1);
}
void	ftwait(int **fd, int count)
{
    int i;

    i = 0;
    while (i < count)
    {
        free(fd[i]);
        i++;
    }
    free(fd);
	while (wait(NULL) != -1)
	{
	}
}

int handle_pipe(t_pipe *pip, char **env)
{
    int exit_status;
    int	**fd;
    int count;
    int i;
    
	i = 0;
    exit_status = 0;
    count = count_pipe(pip);
	fd = allocate_for_pipe(count);
	while (i < count)
	{
		if (i != count - 1)
			pipe(fd[i]);
		if (fork() == 0)
		{
            if (i == 0)
				handle_cmd(pip, NULL, fd[i], env);
			else if (i == count - 1)
				handle_cmd(pip, fd[i - 1], NULL, env);
			else
				handle_cmd(pip, fd[i - 1], fd[i], env);
		}
		if (i != count - 1)
			close(fd[i][1]);
		i++;
        pip = pip->next;
	}
	ftclose(fd, count);
	ftwait(fd, count);
    return(exit_status);
}
