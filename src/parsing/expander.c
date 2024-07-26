/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:34:24 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/07/14 13:47:02 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_word(char *key)
{
	int		i;
	char	*env;
	char	*word;

	key++;
	if (!ft_strncmp(key, "?", 2) || !ft_strncmp(key, "? ", 2)
		|| !ft_strncmp(key, "?\t", 2))
		return (ft_strdup("69"));
	i = 0;
	while (key[i] && key[i] != ' ' && key[i] != '\t' && key[i] != '\n')
		i++;
	word = ft_substr(key, 0, i);
	if (!word)
		return (NULL);
	env = getenv(word);
	free(word);
	if (env)
		return (ft_strdup(env));
	else
		return (ft_strdup(""));
}

char	*copy_word(char *old, char **keys)
{
	int		len;
	char	*start;
	char	*str;
	char	*result;

	start = *keys;
	while (**keys && **keys != ' ' && **keys != '\t' && **keys != '\n')
		(*keys)++;
	while (**keys && (**keys == ' ' || **keys == '\t' || **keys == '\n'))
		(*keys)++;
	len = *keys - start;
	str = ft_substr(start, 0, len);
	if (!str)
	{
		free(old);
		return (NULL);
	}
	if (!old)
		return (str);
	result = ft_strjoin(old, str);
	free(old);
	free(str);
	return (result);
}

char	*add_expanded_word(char *old, char *expanded_word)
{
	char	*final_str;

	if (!expanded_word)
	{
		free(old);
		return (NULL);
	}
	if (old)
	{
		final_str = ft_strjoin(old, expanded_word);
		free(old);
		free(expanded_word);
	}
	else
		final_str = expanded_word;
	return (final_str);
}

char	*env_str(char *keys)
{
	char	*str;
	char	*word;

	str = NULL;
	while (*keys)
	{
		if (*keys == '$')
		{
			word = expand_word(keys);
			str = add_expanded_word(str, word);
			if (!str)
				return (NULL);
			while (*keys && *keys != ' ' && *keys != '\t' && *keys != '\n')
				keys++;
		}
		else
		{
			str = copy_word(str, &keys);
			if (!str)
				return (NULL);
		}
	}
	return (str);
}

t_token	*expand_tokens(t_token *token)
{
	t_token	*t;
	char	*str;

	t = token;
	while (t)
	{
		if ((t->type == WORD && t->content[0] == '$') || t->type == DQUOTE)
		{
			if (t->type == WORD && t->content[0] == '$')
				str = expand_word(t->content);
			else
				str = env_str(t->content);
			if (!str)
				break ;
			free(t->content);
			t->content = str;
		}
		t = t->next;
	}
	if (t)
	{
		clean_tokens(token);
		exit(EXIT_FAILURE);
	}
	return (token);
}
