/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:24:40 by amagnell          #+#    #+#             */
/*   Updated: 2022/11/19 16:20:03 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//returns a string representing int n or NULL if it fails.

size_t	nbr_chr(long n, size_t i)
{
	if (n < 0)
	{
		i++;
		n = -n;
	}
	if (n > 9)
	{
		i = nbr_chr(n / 10, i);
		i = nbr_chr(n % 10, i);
	}
	if (n <= 9)
		i++;
	return (i);
}

static char	*itob(long n, char *str, size_t len)
{
	str[len] = '\0';
	len--;
	while (n > 9)
	{
		str[len] = (n % 10) + '0';
		len--;
		n /= 10;
	}
	str[len] = n + '0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	long	m;

	m = n;
	len = nbr_chr(m, 0);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (m < 0)
	{
		str[0] = '-';
		m = m * -1;
	}
	str = itob(m, str, len);
	return (str);
}
/*
int	main (void)
{
	printf("%s", ft_itoa(-9));
	return (0);
}
*/
//asfdasdf from the back or not idk
