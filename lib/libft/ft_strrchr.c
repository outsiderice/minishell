/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:11:02 by amagnell          #+#    #+#             */
/*   Updated: 2022/10/19 16:17:39 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*a;

	i = ft_strlen(s);
	a = (char *)s;
	if ((char)c == '\0')
		return (&a[i]);
	while (i > 0)
	{
		i--;
		if (a[i] == (char)c)
			return (&a[i]);
	}
	return (NULL);
}
