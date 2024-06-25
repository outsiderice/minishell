/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:19:25 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/17 10:54:07 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// deletes node pointed to by LST using DEL
void	ft_lstdelone(t_list *lst, void (*del) (void *))
{
	if (lst)
	{
		del(lst->content);
		free(lst);
	}
}
