/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:18:19 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/17 10:47:08 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Converts numbers contained in inital part of the string pointed by STR to int
// Returns 0 if it can't. It allows one use of + or - before the number. 
int	ft_atoi(const char *str)
{
	int	i;
	int	a;
	int	n;

	i = 0;
	a = 0;
	n = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		n = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		a = 10 * a + (str[i] - '0');
		i++;
	}
	return (n * a);
}

/*int	main(void)
{
	//	str[] = " +12";
	//printf("%d", atoi(((void*)0)));
	printf("%d", ft_atoi(((void*)0)));
	return (0);
}*/
