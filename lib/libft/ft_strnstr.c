/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:16:42 by amagnell          #+#    #+#             */
/*   Updated: 2022/10/21 15:51:35 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Locates the first ocurrence of string needle in string haystack
//Only searches up to len characters. Characters after '\0' aren't searched.
//Returns ptr to the first character of first occurence of needle.
//Return haystack if needle is an empty string. 
//Returns NULL if it can't find needle in haystack.

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		c;

	i = 0;
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		c = 0;
		while (haystack[i + c] == needle[c] && haystack[i + c] != '\0')
		{
			if (needle[c + 1] == '\0' && (i + c) < len)
			{
				return (&((char *)haystack)[i]);
			}
			c++;
		}
		i++;
	}
	return (NULL);
}

/*int	main(void)
{
	const char	*a = "hello";
	const char	*b = "hell";

	printf("%s", ft_strnstr(a, b, 4));
	return (0);
}*/
