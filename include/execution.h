/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:08:48 by laoubaid          #+#    #+#             */
/*   Updated: 2024/08/03 00:40:19 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <sys/wait.h>
# include <sys/stat.h>

typedef struct s_env
{
	char			*name;
	char			*value;
	int				print_flag;
	struct s_env	*next;
}	t_env;

typedef struct s_param
{
	t_env	*env;
	char	**env_arr;
	t_ast	*ast;
}   t_param;

typedef struct s_pipe  
{
	t_cmd			*cmd;
	t_param			*param;
	struct s_pipe	*next;
}	t_pipe;



int		command_execution(t_param *param);

char	**split_all(char const *s, char c);
char	**ft_free(char **ptr);

int		path(char ***p, char *ev);
int		getpath(char **ev, char *comp);

void	redirecte(t_cmd *cmd, int in, int out, int apd);

/* builtins functions */
int		ft_pwd(t_param *param);
int		ft_cd(t_param *param);
int		ft_echo(char **cmd);
int		ft_unset(t_param *param, char **cmd);

int		builtins(t_param *param, t_cmd *cmd);
int		execute(t_param *param);


/* functions to handle file errors */
int		check_if_path(char *cmd);
int		chdir_errors(char *dir);
int		execution_errors(char *cmd);

void	free_pipe(t_pipe *pip);
int		handle_pipe(t_pipe *pip, char **env);
t_pipe	*pipeline(t_ast *ast, t_param *param);

t_param	*param_init(char **env);

char	*strjoin_optclean(char *s1, char *s2, int flag);

/* functions related to environement */
int		env_edit(t_param *param, char *find, char *value);
void	print_variables(t_param *param);
int		checkifvalid(char *str, int *idx);
int		checkifexist(char *str, t_env *env, int *idx);
char	*env_fetch(char *var, t_env *tmp);
char	**recreate_env(t_env *env_list, char **env);

#endif