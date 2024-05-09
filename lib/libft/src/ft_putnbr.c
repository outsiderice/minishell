/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:07:08 by amagnell          #+#    #+#             */
/*   Updated: 2023/10/14 20:50:34 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int count, long long nbr, char *base, const char *type)
{
	if (nbr < 0 && ft_strchr("di", *type))
	{
		nbr = nbr * -1;
		count = ft_putchar('-');
		if (count == -1)
			return (-1);
	}
	if (nbr >= (int)ft_strlen(base))
	{
		count = ft_putnbr(count, nbr / ft_strlen(base), base, type);
		if (count == -1)
			return (-1);
		count = ft_putnbr(count, nbr % ft_strlen(base), base, type);
	}
	else if (nbr < (int)ft_strlen(base))
		count = count + ft_putchar(base[nbr]);
	return (count);
}
