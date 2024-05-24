/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:40:16 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/24 16:13:22 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*    LIBRARIES    */
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "../lib/readline/readline.h"
# include "../lib/readline/history.h"
# include "../lib/libft/include/libft.h"

/*    STRUCTURES    */
typedef	struct s_ms
{
	t_env		*env;
	t_tokens	*tokens;
	//t_args		*args;
	//t_pipes		*pipes;
	int			exec_value;
	int			sh_lvl;
	char		*new_pwd;
	char		*old_pwd;
	int			pid;
}	t_ms;

typedef struct s_tokens
{
	int				type;
	char			*tok;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_env
{
	char			*v_name;
	char			*v_cont;
	struct s_list	*next;
}	t_env;


/*    main.c    */
void	ft_minishell(char **env);

/*    get_input.c    */
char	*ft_readline(void);

/*    check_quotes.c    */
int		ft_check_quotes(const char *line);
int		ft_quote_len(const char *line, char type);

/*    tokenize.c    */
void	ft_tokenize(const char *line);
// void		ft_get_toks(const char *line, t_tokens **tokens);
// int		ft_isword(const char *line, t_tokens **tokens);
// int		ft_isoperator(const char *line, t_tokens **tokens);

/*    parser.c    */
void	ft_parse(t_tokens *tokens);

#endif
