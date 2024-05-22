/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:47:27 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/22 10:05:21 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H


/*          STRUCT         */
//type = 1 ->word
//type = 2 ->operator //might assign from 2-5 for redirections if needed
typedef struct	s_tokens
{
	int				type;
	char			*token;
	struct s_tokens	*next;
}					t_tokens;

void	ft_tokenize(const char *line);

/*          UTILS          */
void		ft_addtok(const char *line, int len, t_tokens **tokens);
// void		ft_init_tokens(t_tokens **tokens);
int			ft_ismetachar(char c);

#endif