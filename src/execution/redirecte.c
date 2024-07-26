/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecte.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:53:30 by laoubaid          #+#    #+#             */
/*   Updated: 2024/07/21 21:38:35 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/execution.h"

void count_redir(t_redir *tmp, int *in, int *out)
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

void    duping(t_redir *tmp, int *inputs, int *outputs)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (tmp)
    {
        if (tmp->redir_type == R_STD_OUT)
        {
            outputs[j] = open(tmp->filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
            dup2(outputs[j], STDOUT_FILENO);
            close(outputs[j++]);
        }
        else if (tmp->redir_type == R_STD_IN)
        {
            inputs[i] = open(tmp->filename, O_RDONLY);
            if (inputs[i] == -1)
            {
                perror("file");
                exit(1);
            }
            dup2(inputs[i], STDIN_FILENO);
            close(inputs[i++]);
        }
        tmp = tmp->next;
    }
}

void	redirecte(t_cmd *cmd)
{
	int 	input_counter;
    int 	output_counter;
    int 	*inputs;
	int		*outputs;
    t_redir *tmp;

    input_counter = 0;
    output_counter = 0;
    count_redir(cmd->redirs, &input_counter, &output_counter);
    inputs = malloc(sizeof(int) * input_counter);
    outputs = malloc(sizeof(int) * output_counter);
    duping(cmd->redirs, inputs, outputs);
}
