/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:10:00 by amagnell          #+#    #+#             */
/*   Updated: 2022/11/09 14:38:54 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//creates a new string with succesive applications of function f to each
//character of string s. The index of string s is passed as the first argument
//of f function.
//returns a new string or NULL if the allocation fails.

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	char			*a;
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	a = ft_calloc(i + 1, sizeof(char));
	if (a == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		a[i] = f(i, s[i]);
		i++;
	}
	a[i] = '\0';
	return (a);
}
