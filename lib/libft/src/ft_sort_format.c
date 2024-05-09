/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:07:31 by amagnell          #+#    #+#             */
/*   Updated: 2023/10/14 20:48:30 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sort_format(const char *type, va_list args)
{
	int	count;

	count = 0;
	if (*type == 'c')
		count = ft_putchar(va_arg(args, int));
	else if (*type == 's')
		count = ft_putstr(va_arg(args, char *));
	else if (*type == 'p')
		count = ft_putptr(va_arg(args, unsigned long));
	else if (ft_strchr("di", *type))
		count = ft_nbrs(va_arg(args, int), type);
	else if (ft_strchr("uxX", *type))
		count = ft_nbrs(va_arg(args, unsigned int), type);
	else if (*type == '%')
		count = ft_putchar('%');
	return (count);
}
