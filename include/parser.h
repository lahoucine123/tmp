/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 20:09:43 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/07/13 16:39:17 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_type
{
	WORD,
	PIPE,
	AND,
	OR,
	GREAT,
	DGREAT,
	LESS,
	DLESS,
	DQUOTE,
	SQUOTE,
	RPAREN,
	LPAREN
}	t_type;

typedef	enum e_redir_type
{
	R_STD_OUT,
	R_APPEND,
	R_STD_IN,
	R_HEREDOC
}	t_redir_type;

typedef struct s_token
{
	t_type			type;
	char			*content;
	int				prec;
	struct s_token	*next;
	struct s_token	*previous;
}	t_token;

typedef struct s_redir
{
	t_redir_type	redir_type;
	char			*filename;
	struct s_redir	*previous;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char	**simple_cmd;
	t_redir	*redirs;
}	t_cmd;

typedef	struct s_ast
{
	t_type			type;
	struct s_ast	*left;
	struct s_ast	*right;
	t_cmd			*cmd;
}	t_ast;


int		parser(char *input, t_ast **ast);
void	*clean_tokens(t_token *token);
t_token	*tokenizer(char *input);
t_token	*expand_tokens(t_token *tokens);
int		is_words(t_token *token);
int		is_rediration(t_token *token);
int		is_op(t_token *token);
t_ast	*build_ast(t_token *token);
int		verify_grammar(t_token **token);
int		grammar(t_token *token);
void	*clean_ast(t_ast *ast);
t_ast	*fill_branches(int	min_prec, t_token **token);

//to be deleted
void	print_tokens(t_token *tokens);
void	print_cmd(t_cmd *cmd);
void	print_ast(t_ast *ast);

#endif