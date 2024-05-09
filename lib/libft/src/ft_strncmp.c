/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:12:06 by amagnell          #+#    #+#             */
/*   Updated: 2022/10/19 16:16:54 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Compare two strings, s1 and s2, up to n characters.
//If they're the same returns 0
//if s1 is bigger than s2 it returns more than 0, and otherwise less than 0.

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*d1;
	unsigned char	*d2;

	d1 = (unsigned char *)s1;
	d2 = (unsigned char *)s2;
	i = 0;
	while (i < n - 1 && d1[i] && d2[i] && d1[i] == d2[i])
		i++;
	if (n == 0)
		return (0);
	return (d1[i] - d2[i]);
}

//diff has to stop comparing at n chars, it doesn't right now.
