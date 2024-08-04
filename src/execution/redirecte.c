/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecte.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:53:30 by laoubaid          #+#    #+#             */
/*   Updated: 2024/08/04 20:17:31 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/execution.h"

void	count_redir(t_redir *tmp, int *in, int *out, int *app)
{
	while (tmp)
	{
		if (tmp->redir_type == R_STD_OUT)
			(*out)++;
		else if (tmp->redir_type == R_STD_IN)
			(*in)++;
		tmp = tmp->next;
	}
}

int	duping_suite(int *tab, int i, t_redir *tmp, int flag)
{
	if (flag == 1)
		tab[i] = open(tmp->filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (flag == 2)
		tab[i] = open(tmp->filename, O_RDONLY);
	if (flag == 3)
		tab[i] = open(tmp->filename, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (tab[i] == -1)
	{
		perror("file");
		exit(1);
	}
	if (flag == 1 || flag == 3)
		dup2(tab[i], STDOUT_FILENO);
	else
		dup2(tab[i], STDIN_FILENO);
	close(tab[i]);
	return (i + 1);
}

void	duping(t_redir *tmp, int *inputs, int *outputs, int *appends)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (tmp)
	{
		if (tmp->redir_type == R_STD_OUT)
			j = duping_suite(outputs, j, tmp, 1);
		else if (tmp->redir_type == R_STD_IN)
			i = duping_suite(inputs, i, tmp, 2);
		else if (tmp->redir_type == R_APPEND)
			k = duping_suite(appends, k, tmp, 3);
		tmp = tmp->next;
	}
}

void	redirecte(t_cmd *cmd, int in_count, int out_count,int apd_count)
{
	int 	*inputs;
	int		*outputs;
	int		*appends;
	t_redir	*tmp;

	count_redir(cmd->redirs, &in_count, &out_count, &apd_count);
	inputs = malloc(sizeof(int) * in_count);
	outputs = malloc(sizeof(int) * out_count);
	appends = malloc(sizeof(int) * apd_count);
	duping(cmd->redirs, inputs, outputs, appends);
	free(inputs);
	free(outputs);
	free(appends);
}
