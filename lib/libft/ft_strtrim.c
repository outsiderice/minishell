/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 18:46:52 by amagnell          #+#    #+#             */
/*   Updated: 2022/11/03 19:13:31 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//trim the characters in SET from string S1
//From both the start of the string and the end of it
//UNTIL it finds a character not in SET
//returns new trimmed string or NULL if it can't create it.

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	j = ft_strlen(s1);
	while (ft_strrchr(set, s1[j]) && j)
		j--;
	str = ft_substr(s1, i, j - i + 1);
	return (str);
}
