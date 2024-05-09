/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:06:41 by amagnell          #+#    #+#             */
/*   Updated: 2023/10/14 20:48:03 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nbrs(unsigned long nbr, const char *type)
{
	int		count;
	char	*base;

	count = 0;
	if (ft_strchr("diu", *type))
		base = "0123456789";
	else if (*type == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (ft_strchr("puxX", *type))
	{
		count = count + ft_putunbr(count, nbr, base, type);
		if (count == -1)
			return (-1);
	}
	else
	{
		count = count + ft_putnbr(count, nbr, base, type);
		if (count == -1)
			return (-1);
	}
	return (count);
}
