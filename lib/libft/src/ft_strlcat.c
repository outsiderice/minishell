/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:06:16 by amagnell          #+#    #+#             */
/*   Updated: 2022/10/19 16:16:30 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Attaches string src to the end of dst. 
//Only up to dstsize (strlen(dst)) - 1 characters.
//Adds Null at the end. Unless dstsize is 0 or dst is longer than dstsize.
//Returns length of dst + src.

size_t	ft_strlcat(char *dst, const void *src, size_t dstsize)
{
	size_t		dstlen;
	size_t		i;
	char		*src1;

	src1 = (char *)src;
	dstlen = ft_strlen(dst);
	i = dstlen;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (i < dstsize - 1 && src1[i - dstlen] != '\0')
	{
		dst[i] = src1[i - dstlen];
		i++;
	}
	dst[i] = '\0';
	if (dstlen > dstsize)
		return (dstsize + ft_strlen(src));
	return (dstlen + ft_strlen(src));
}

/*int	main(void)
{
	char str1[] = "pqrstuvwxyz";
	char str2[] = "abcd";

	printf("%lu", ft_strlcat(str1, str2, 1));
	return (0);
}*/
