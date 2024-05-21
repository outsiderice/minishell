/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:47:08 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/21 08:59:13 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "../lib/libft/include/libft.h"
#include <stdio.h>

void	ft_init_tokens()
{}
char	ft_isspace(char c)
{
	if (c == ' ' || c == '	')
		return (c);	
}

void	ft_tokenize(const char *line)
{
	ft_init_tokens();
	return ;
}
