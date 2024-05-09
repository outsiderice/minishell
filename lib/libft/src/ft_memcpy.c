/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:22:45 by amagnell          #+#    #+#             */
/*   Updated: 2022/10/10 16:15:14 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)src;
	b = (unsigned char *)dst;
	i = 0;
	if (!dst && !src)
		return (dst);
	while (i < n)
	{
		b[i] = a[i];
		i++;
	}
	return (dst);
}

/*int	main (void)
{
	char	str[] = "holas";
	printf("%s", ft_memcpy(str + 2, str, strlen(str + 2)));
	return (0);
}*/
