/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:02:33 by laoubaid          #+#    #+#             */
/*   Updated: 2024/07/20 19:03:30 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/execution.h"
    
void    print_error(char *name, char *err)
{
    if (name)
    {
        write(2, name, ft_strlen(name));
        write(2, ": ", 3);
    }
    write(2, err, ft_strlen(err));
}

int check_if_path(char *cmd)
{
    int i;

    i = 0;
    while (cmd[i])
    {
        if (cmd[i] == '/')
            return (1);
        i++;
    }
    return (0);
}

int    execution_errors(char *cmd)
{
    struct stat filetype;

    if (!check_if_path(cmd))
        return (0);
    if (stat(cmd, &filetype) == 0)
    {
        if (S_ISDIR(filetype.st_mode))
        {
            print_error(cmd, "Is a directory\n");
            return (126);
        }
    }
    else
    {
        perror(cmd);
        return (126);
    }
    if (access(cmd, X_OK) != 0)
        perror("error");
    return (0);
}