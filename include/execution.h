/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:08:48 by laoubaid          #+#    #+#             */
/*   Updated: 2024/07/26 18:58:04 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <sys/wait.h>
# include <sys/stat.h>

typedef struct s_env
{
    char    *name;
    char    *value;
    struct s_env *next;
}   t_env;

typedef struct s_param
{
    t_env   *env;
    char    **env_arr;
    t_ast   *ast;
}   t_param;

typedef struct s_pipe  
{
    t_cmd *cmd;
    struct s_pipe *next;
}   t_pipe;



int	    command_execution(t_cmd *cmd, char **env);

char	**split_all(char const *s, char c);
char	**ft_free(char **ptr);

int		path(char ***p, char *ev);
int		getpath(char **ev);

void	redirecte(t_cmd *cmd);

int    execute(t_param *param);

int     check_if_path(char *cmd);
int     execution_errors(char *cmd);

int     handle_pipe(t_pipe *pip, char **env);
t_pipe  *pipeline(t_ast *ast);

#endif