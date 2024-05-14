/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:18:19 by amagnell          #+#    #+#             */
/*   Updated: 2023/11/06 20:07:03 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
//#include "libft.h"

//converts numbers contained in inital part of the string pointed by str to int
//returns 0 if it can't. it allows one use of + or - before the number. 

int	ft_atoi(const char *str)
{
	int	i;
	int	a;
	int	n;

	i = 0;
	a = 0;
	n = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
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

long	ft_atol(const char *str)
{
	long	i;
	long	a;
	long	n;

	i = 0;
	a = 0;
	n = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
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

/*
int	main(void)
{
	char *str = "+123";

	printf("%d", atoi(str));
	printf("\n");
	printf("%d", ft_atoi(str));
	return (0);
}
*/
