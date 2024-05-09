/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:17:47 by amagnell          #+#    #+#             */
/*   Updated: 2022/10/31 15:33:02 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)src;
	b = (unsigned char *)dst;
	i = 0;
	if (len)
	{
		if (a < b)
		{
			while (len--)
				b[len] = a[len];
		}
		else if (b < a)
		{
			while (i < len)
			{
				b[i] = a[i];
				i++;
			}
		}
	}
	return (dst);
}

/*int	main(void)
{
	char	str[] = "holas";

	printf("%s", ft_memmove(str + 3, str, 200));
	return (0);
}*/
