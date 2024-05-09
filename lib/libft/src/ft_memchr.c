/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:13:41 by amagnell          #+#    #+#             */
/*   Updated: 2022/10/19 12:21:06 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//locates first ocurrence of c (converted to an unsigned char) in string s
//returns a pointer to the byte located or NULL if there's no c character in
//n bytes.

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*a;

	i = 0;
	a = (unsigned char *)s;
	while (i < n)
	{
		if (a[i] == (unsigned char)c)
			return (&a[i]);
		i++;
	}
	return (NULL);
}
