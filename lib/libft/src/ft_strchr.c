/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:10:06 by amagnell          #+#    #+#             */
/*   Updated: 2022/11/01 15:23:57 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Locates the first instance of int c (converted to char) in char *s.
//It should be able to locate '\0' at the end of the line if it's the argument.
//Returns a pointer (*a) to the located character.

char	*ft_strchr(const char *s, int c)
{
	int				i;
	char			*a;

	i = 0;
	a = (char *)s;
	while (a[i] != '\0')
	{
		if (a[i] == (char)c)
			return (&a[i]);
		i++;
	}
	if ((char)c == '\0')
		return (&a[i]);
	return (NULL);
}

/*
int	main(void)
{
	printf("%s", ft_strchr());
	return (0);
}
*/
