/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:31:32 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/07/14 13:47:02 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_rediration(t_token *token)
{
	if (token->type == GREAT || token->type == DGREAT
		|| token->type == LESS || token->type == DLESS)
		return (1);
	return (0);
}

int	is_words(t_token *token)
{
	if (token->type == WORD || token->type == DQUOTE || token->type == SQUOTE)
		return (1);
	return (0);
}

int	is_op(t_token *token)
{
	if (token->type == PIPE || token->type == OR || token->type == AND)
		return (1);
	return (0);
}

void	*free_array(char **array)
{
	int	index;

	index = 0;
	if (!array)
		return (NULL);
	while (array[index])
	{
		free(array[index]);
		index++;
	}
	free(array);
	return (NULL);
}

void	*clean_cmd(t_cmd *cmd)
{
	t_redir	*redirs;
	t_redir	*tmp_redirs;

	free_array(cmd->simple_cmd);
	redirs = cmd->redirs;
	while (redirs)
	{
		tmp_redirs = redirs;
		redirs = redirs->next;
		free(tmp_redirs->filename);
		free(tmp_redirs);
	}
	free(cmd);
	return (NULL);
}

void	*clean_ast(t_ast *ast)
{
	if (!ast)
		return (NULL);
	if (ast->cmd)
		clean_cmd(ast->cmd);
	if (ast->left)
		clean_ast(ast->left);
	if (ast->right)
		clean_ast(ast->right);
	free(ast);
	return (NULL);
}

t_ast	*new_ast(t_ast *left, t_ast *right, t_cmd *cmd, t_type type)
{
	t_ast	*ast;

	ast = (t_ast *)malloc(sizeof(t_ast));
	if (!ast)
	{
		clean_ast(left);
		clean_ast(right);
		return (NULL);
	}
	ast->type = type;
	ast->left = left;
	ast->right = right;
	ast->cmd = cmd;
	return (ast);
}

int	cmd_len(t_token *token)
{
	int	len;

	len = 0;
	while (token && !is_op(token) && token->type != RPAREN)
	{
		if (is_words(token))
			len++;
		if (is_rediration(token))
			token = token->next;
		token = token->next;
	}
	return (len);
}

char	**get_simple_cmd(t_token *token)
{
	char	**simple_cmd;
	int		len;

	len = cmd_len(token) +1;
	simple_cmd = (char **)malloc(len * sizeof(char *));
	if (!simple_cmd)
		return (NULL);
	simple_cmd[len -1] = NULL;
	len = 0;
	while (token && !is_op(token) && token->type != RPAREN)
	{
		if (is_words(token))
		{
			simple_cmd[len] = ft_strdup(token->content);
			if (!simple_cmd[len])
				return (free_array(simple_cmd));
			len++;
		}
		else
			token = token->next;
		token = token->next;
	}
	return (simple_cmd);
}

int	has_redirs(t_token *token)
{
	while (token && !is_op(token) && token->type != RPAREN)
	{
		if (!is_words(token))
			return (1);
		token = token->next;
	}
	return (0);
}

t_redir	*new_redir(t_token *token, t_redir *previous)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->previous = previous;
	redir->next = NULL;
	if (token->type == GREAT)
		redir->redir_type = R_STD_OUT;
	else if (token->type == LESS)
		redir->redir_type = R_STD_IN;
	else if (token->type == DGREAT)
		redir->redir_type = R_APPEND;
	else if (token->type == DLESS)
		redir->redir_type = R_HEREDOC;
	token = token->next;
	redir->filename = ft_strdup(token->content);
	if (!(redir->filename))
	{
		free(redir);
		return (NULL);
	}
	return (redir);
}

t_redir	*get_redirs(t_token *token)
{
	t_redir	*redirs;
	t_redir	*current;

	redirs = NULL;
	while (token && !is_op(token) && token->type != RPAREN)
	{
		if (!is_words(token))
		{
			if (redirs)
			{
				current->next = new_redir(token, current);
				current = current->next;
			}
			else
			{
				redirs = new_redir(token, NULL);
				current = redirs;
			}
			if (!current)
				return (NULL);
			token = token->next;
		}
		token = token->next;
	}
	return (redirs);
}

t_cmd	*new_cmd(t_token **token)
{
	t_cmd	*cmd;
	int		redirs;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	redirs = has_redirs(*token);
	cmd->simple_cmd = get_simple_cmd(*token);
	if (redirs)
		cmd->redirs = get_redirs(*token);
	else
		cmd->redirs = NULL;
	if (!cmd->simple_cmd || (redirs && !(cmd->redirs)))
		return (clean_cmd(cmd));
	while (*token && !is_op(*token) && (*token)->type != RPAREN)
		*token = (*token)->next;
	return (cmd);
}

t_ast	*paren_ast(t_token **token)
{
	t_ast	*ast;
	t_ast	*l_ast;

	ast = new_ast(NULL, NULL, NULL, (*token)->type);
	if (!ast)
		return (NULL);
	*token = (*token)->next;
	l_ast = fill_branches(1, token);
	if (!l_ast)
		return (clean_ast(ast));
	*token = (*token)->next;
	ast->left = l_ast;
	if (has_redirs(*token))
	{
		ast->cmd = new_cmd(token);
		if (!ast->cmd)
			return (clean_ast(ast));
	}
	return (ast);
}

t_ast	*make_command(t_token **token)
{
	t_ast	*ast;

	if ((*token)->type == LPAREN)
		ast = paren_ast(token);
	// {
	// 	*token = (*token)->next;
	// 	ast = fill_branches(1, token);
	// 	*token = (*token)->next;
	// }
	else
	{
		ast = new_ast(NULL, NULL, NULL, WORD);
		if (!ast)
			return (NULL);
		ast->cmd = new_cmd(token);
		if (!(ast->cmd))
			return (clean_ast(ast));
	}
	return (ast);
}

t_ast	*fill_branches(int min_prec, t_token **token)
{
	t_ast	*left;
	t_ast	*right;
	int		next_min_prec;
	t_type	type;

	left = make_command(token);
	if (!left)
		return (NULL);
	while (1)
	{
		if (!*token || !is_op(*token) || (*token)->prec < min_prec)
			break ;
		next_min_prec = (*token)->prec +1;
		type = (*token)->type;
		*token = (*token)->next;
		right = fill_branches(next_min_prec, token);
		if (!right)
			return (clean_ast(left));
		left = new_ast(left, right, NULL, type);
		if (!left)
			return (NULL);
	}
	return (left);
}

t_ast	*build_ast(t_token *token)
{
	t_ast	*ast;

	ast = fill_branches(1, &token);
	if (!ast)
	{
		clean_tokens(token);
		exit(EXIT_FAILURE);
	}
	return (ast);
}
