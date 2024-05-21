/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:47:27 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/21 08:52:22 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

typedef struct s_tokens
{
    int             type;
    char            *token;
    struct  s_token *next;
} t_tokens;


void	ft_tokenize(const char *line);

#endif