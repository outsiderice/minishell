/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:47:27 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/21 15:31:29 by amagnell         ###   ########.fr       */
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
t_tokens	*ft_addtok(t_tokens *tok, char *line, int len);
void		ft_init_tokens(t_tokens *tok);
int			ft_ismetachar(char c);

#endif