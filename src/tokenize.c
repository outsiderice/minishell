/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:47:08 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/20 12:44:16 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "../lib/libft/include/libft.h"
#include <stdio.h>

void	ft_tokenize(const char *line)
{
	char	**array;
	int		i;

	i = 0;
	array = ft_split(line, ' ');
	while (array[i])
	{
		printf("%s\n", &*array[i]);
		i++;
	}
	//to lex or not to lex
	//once we have this array with tokens we need to take the steps towards execution:
	//1.check if there's a redirection sign
	//2.check if it's a builtin
	//3.check syntax
	//4.execute
	return ;
}
