/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:07:30 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/17 10:56:21 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Iterate LST to apply f to all its CONTENT
void	ft_lstiter(t_list *lst, void (*f) (void *))
{
	t_list	*node;

	while (lst != NULL)
	{
		node = lst;
		lst = lst->next;
		f(node->content);
	}
}
