/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:30:27 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/07 12:11:15 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//creates a string from S at START which is at most LEN size.
//Returns the substring created or NULL if it fails.
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (start >= ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	if (ft_strlen(s) - start > len)
	{
		str = malloc (len + 1);
		if (str == NULL)
			return (NULL);
		str[len] = '\0';
		ft_memmove(str, s + start, len);
		return (str);
	}
	str = malloc (ft_strlen(s) - start + 1);
	if (str == NULL)
		return (NULL);
	ft_memmove(str, s + start, ft_strlen(s) - start);
	str[ft_strlen(s) - start] = '\0';
	return (str);
}
/*
int	main(void)
{
	char	str[] = "hola";

	printf("%s", ft_substr(str, 0, 6557657657));
	return (0);
}
*/
