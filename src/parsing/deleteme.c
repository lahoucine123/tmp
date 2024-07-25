#include "../../include/minishell.h"

void	print_tokens(t_token *tokens)
{
	int	id = 1;
	if (!tokens)
		printf("tokens: NULL\n");
	while (tokens)
	{
		printf("token: %d | type: ", id);
		if (tokens->type == WORD)
			printf(" WORD  | ");
		else if (tokens->type == PIPE)
			printf(" PIPE  | ");
		else if (tokens->type == AND)
			printf("  AND  | ");
		else if (tokens->type == OR)
			printf("  OR   | ");
		else if (tokens->type == GREAT)
			printf(" GREAT | ");
		else if (tokens->type == DGREAT)
			printf("DGREAT | ");
		else if (tokens->type == LESS)
			printf(" LESS  | ");
		else if (tokens->type == DLESS)
			printf(" DLESS | ");
		else if (tokens->type == DQUOTE)
			printf("DQUOTE | ");
		else if (tokens->type == SQUOTE)
			printf("SQUOTE | ");
		else if (tokens->type == RPAREN)
			printf("RPAREN | ");
		else if (tokens->type == LPAREN)
			printf("LPAREN | ");
		printf("prec: %d | ", tokens->prec);
		if (tokens->content)
			printf("content: %s\n", tokens->content);
		else
			printf("content: NULL\n");
		tokens = tokens->next;
		id++;
	}
}

void	print_cmd(t_cmd *cmd)
{
	t_redir	*crnt_redir;

	if (!cmd)
		return ;
	crnt_redir = cmd->redirs;
	printf("--------------------------------- cmd ---------------------------------\n");
	if ((cmd->simple_cmd)[0])
		printf("cmd name: %s\n", (cmd->simple_cmd)[0]);
	else
		printf("cmd name: NULL\n");
	printf("- - - - - - - - - - - - - - - - -params - - - - - - - - - - - - - - - -\n");
	if ((cmd->simple_cmd)[0])
	{
		int i = 1;
		while ((cmd->simple_cmd)[i])
		{
			printf("%s -> ", (cmd->simple_cmd)[i]);
			i++;
		}
	}
	printf("NULL\n");
	printf("- - - - - - - - - - - - - - - - -redirs- - - - - - - - - - - - - - - - \n");
	while (crnt_redir)
	{
		printf("redir type: ");
		if (crnt_redir->redir_type == R_STD_OUT)
			printf("R_STD_OUT");
		else if (crnt_redir->redir_type == R_STD_IN)
			printf("R_STD_IN ");
		else if (crnt_redir->redir_type == R_APPEND)
			printf("R_APPEND ");
		else if (crnt_redir->redir_type == R_HEREDOC)
			printf("R_HEREDOC");
		printf(" | filename: %s\n", crnt_redir->filename);
		crnt_redir = crnt_redir->next;
	}
	printf("-----------------------------------------------------------------------\n");
}

void	print_ast(t_ast *ast)
{
	if (!ast)
		return;
	if (ast->cmd && ast->type == WORD)
		printf("\e[32m");
	else
		printf("\e[31m");
	printf("############################### ast node ###############################\n");
	if (!ast)
	{
		printf("AST is: NULL\n");
		printf("########################################################################\n");
		return ;
	}
	printf("AST type: ");
	if (ast->type == PIPE)
		printf("PIPE\n");
	else if (ast->type == AND)
		printf("AND\n");
	else if (ast->type == OR)
		printf("OR\n");
	else if (ast->type == LPAREN)
		printf("LPAREN\n");
	else if (ast->type == WORD)
		printf("WORD\n");
	else if (ast->type == -1)
		printf("NULL(-1)\n");
	if (ast->cmd)
	{
		printf("AST COMMAND:\n");
		print_cmd(ast->cmd);
	}
	else
		printf("AST COMMAND: NULL\n");
	printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	if (ast->left)
	{
		printf("Left AST NODE:\n");
		print_ast(ast->left);
		if (ast->cmd && ast->type == WORD)
			printf("\e[32m");
		else
			printf("\e[31m");
	}
	else
		printf("Left AST NODE: NULL\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	if (ast->right)
	{
		printf("Right AST NODE:\n");
		print_ast(ast->right);
		if (ast->cmd && ast->type == WORD)
			printf("\e[32m");
		else
			printf("\e[31m");
	}
	else
		printf("Right AST NODE: NULL\n");
	printf("########################################################################\n");
	printf("\e[0m");
}