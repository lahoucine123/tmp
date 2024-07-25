/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:52:40 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/07/19 02:54:29 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	simple_cmd(t_token **token)
{
	if (!*token || (!is_words(*token) && !is_rediration(*token)))
		return (1);
	while (*token && (is_words(*token) || is_rediration(*token)))
	{
		if (is_rediration(*token))
		{
			*token = (*token)->next;
			if (!*token || !is_words(*token))
				return (1);
		}
		if (!(*token)->content)
			return (1);
		*token = (*token)->next;
	}
	return (0);
}

int	full_cmd(t_token **token)
{
	if ((*token) && (*token)->type == LPAREN)
	{
		*token = (*token)->next;
		if (verify_grammar(token) || !*token || (*token)->type != RPAREN)
			return (1);
		*token = (*token)->next;
		while (*token && is_rediration(*token))
		{
			*token = (*token)->next;
			if (!*token || !is_words(*token))
				return (1);
			*token = (*token)->next;
		}
		return (0);
	}
	else
		return (simple_cmd(token));
}

int	verify_grammar(t_token **token)
{
	if (full_cmd(token))
		return (1);
	if (!*token || (*token)->type == RPAREN)
		return (0);
	if (is_op(*token))
	{
		*token = (*token)->next;
		return (verify_grammar(token));
	}
	return (1);
}

int	grammar(t_token *token)
{
	if (verify_grammar(&token) || token)
	{
		ft_putstr_fd("\e[31mparsing problem\e[0m\n", 2);
		return (1);
	}
	// printf("\e[32mgrammar is all good\e[0m\n\n");
	return (0);
}
