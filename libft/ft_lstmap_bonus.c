/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:08:32 by kez-zoub          #+#    #+#             */
/*   Updated: 2023/11/25 01:16:46 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ml(t_list *l, t_list *n, void *(*f)(void *), void (*d)(void *))
{
	t_list	*current;
	void	*content;

	current = n;
	l = l->next;
	while (l)
	{
		content = f(l->content);
		current->next = ft_lstnew(content);
		if (!current->next)
		{
			d(content);
			ft_lstclear(&n, d);
			return (NULL);
		}
		current = current->next;
		l = l->next;
	}
	return (n);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	content = f(lst->content);
	new_lst = ft_lstnew(content);
	if (!new_lst)
	{
		del(content);
		return (NULL);
	}
	new_lst = ml(lst, new_lst, f, del);
	return (new_lst);
}
