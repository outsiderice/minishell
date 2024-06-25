/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:43:11 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/17 10:48:06 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Writes 0s to n bytes of string pointed by s.
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
