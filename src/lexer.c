/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:47:08 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/16 13:42:26 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
# include "../lib/libft/include/libft.h"

void ft_lexer(const char *line)
{
    //split line by spaces, make sure that it doesn't count spaces inside quotes
    //store by types the strings in the array
    ft_split(line, ' ');
}