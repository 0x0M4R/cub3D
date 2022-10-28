/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdalla <oabdalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 09:20:22 by oabdalla          #+#    #+#             */
/*   Updated: 2021/10/12 13:35:22 by oabdalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_lstdup(void *content)
{
	t_list	*temp;

	temp = malloc(sizeof(t_list));
	if (!temp)
		return (NULL);
	temp->content = content;
	temp->next = NULL;
	return (temp);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*dup;

	if (lst == NULL)
		return (NULL);
	dup = ft_lstdup(f(lst->content));
	lst = lst->next;
	while (lst)
	{
		temp = ft_lstdup(f(lst->content));
		if (!temp)
		{
			ft_lstclear(&dup, del);
			return (NULL);
		}
		ft_lstadd_back(&dup, temp);
		lst = lst->next;
	}
	return (dup);
}
