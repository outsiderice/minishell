/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 19:58:13 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/10 09:04:26 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Checks if int c is alphanumeric.
// If true returns 1 and if false 0.
int	ft_isalnum(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

/*int	main(void)
{
	printf("%d", isalnum(' '));
	printf("%d", ft_isalnum(' '));
	return (0);
}*/
