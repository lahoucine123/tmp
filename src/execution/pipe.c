/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 01:28:54 by laoubaid          #+#    #+#             */
/*   Updated: 2024/08/04 21:24:14 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/execution.h"

void	free_pipe(t_pipe *pip)
{
	t_pipe	*tmp;

	while (pip->next)
	{
		tmp = pip->next;
		free(pip);
		pip = tmp;
	}
	free(pip);
}

int	**allocate_for_pipe(t_pipe *pip, int *n)
{
	int	i;
	int	**fd;

	i = 0;
	*n = 0;
	while (pip)
	{
		(*n)++;
		pip = pip->next;
	}
	fd = malloc(sizeof(int *) * (*n));
	while (i < *n)
	{
		fd[i] = malloc(2 * sizeof(int));
		i++;
	}
	return (fd);
}

int	handle_cmd(t_pipe *pip, int *fdin, int *fdout, char **env)
{
	int	exit_status;

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
	exit_status = builtins(pip->param, pip->cmd);
	if (exit_status != -1)
		exit (exit_status);
	if (!check_if_path(pip->cmd->simple_cmd[0]))
		path(&(pip->cmd->simple_cmd), env[getpath(env, "PATH=")]);
	redirecte(pip->cmd, 0, 0, 0);
	exit_status = execution_errors(pip->cmd->simple_cmd[0]);
	if (exit_status)
		exit(exit_status);
	execve(pip->cmd->simple_cmd[0], pip->cmd->simple_cmd, env);
	if (pip->cmd->simple_cmd[0])
		write(2, pip->cmd->simple_cmd[0], ft_strlen(pip->cmd->simple_cmd[0]));
	write(2, ": command not found\n", 20);
	exit(127);
}

int	closexwait(int **fd, int count, int pid)
{
	int	i;
	int	exit_status;

	i = count;
	exit_status = 0;
	while (count - 2 >= 0)
	{
		close(fd[count - 2][0]);
		close(fd[count - 2][1]);
		count--;
	}
	count = i;
	i = 0;
	while (i < count)
		free(fd[i++]);
	free(fd);
	waitpid(pid, &exit_status, 0);
	while (wait(NULL) != -1)
	{
	}
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	return (-1);
}

int	handle_pipe(t_pipe *pip, char **env)
{
	int	exit_status;
	int	**fd;
	int	count;
	int	i;
	int	pid;
		
	i = 0;
	exit_status = 0;
	fd = allocate_for_pipe(pip, &count);
	while (i < count)
	{
		if (i != count - 1)
			pipe(fd[i]);
		pid = fork();
		if (!pid)
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
	exit_status = closexwait(fd, count, pid);
	return(exit_status);
}
