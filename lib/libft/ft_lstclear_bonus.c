/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:33:52 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/17 10:53:07 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// deletes LST node by node using DEL
void	ft_lstclear(t_list **lst, void (*del) (void *))
{
	t_list	*node;
	t_list	*to_delete;

	node = *lst;
	while (node != NULL)
	{
		to_delete = node;
		node = node->next;
		del(to_delete->content);
		free(to_delete);
	}
	*lst = NULL;
}
