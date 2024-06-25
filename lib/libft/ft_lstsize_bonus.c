/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:09:15 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/23 17:03:21 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	if (lst)
	{
		i = 1;
		while (lst->next != NULL)
		{
			i++;
			lst = lst->next;
		}
		return (i);
	}
	return (0);
}
