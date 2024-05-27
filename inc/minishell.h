/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:40:16 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/27 17:35:33 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*    LIBRARIES    */
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <dirent.h>
# include "../lib/readline/readline.h"
# include "../lib/readline/history.h"
# include "../lib/libft/include/libft.h"

/*    STRUCTURES    */
typedef	struct s_ms
{
	t_env		*env;
	t_tokens	*tokens;
	t_args		*args;
	//t_pipes		*pipes;
	int			exec_value;
	int			sh_lvl;
	char		*new_pwd;
	char		*old_pwd;
	int			pid;
}	t_ms;

typedef struct s_args
{
	char			*arg;
	struct s_args	*next;
}	t_args;

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
	struct s_env	*next;
}	t_env;

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

/*    main.c    */
void	ft_minishell(t_ms *ms);

/*    environment.c   */		//to initialize t_env

/*    signals.c    */


/*    get_input.c    */
char	*ft_readline(void);

/*    check_quotes.c    */
int		ft_check_quotes(const char *line);
int		ft_quote_len(const char *line, char type);

/*    tokenize.c    */
void	ft_tokenize(const char *line, t_ms *ms);
// void		ft_get_toks(const char *line, t_tokens **tokens);
// int		ft_isword(const char *line, t_tokens **tokens);
// int		ft_isoperator(const char *line, t_tokens **tokens);

/*    token_utils.c    */
void	ft_addtok(const char *line, int len, int type, t_tokens **tokens);
int		ft_ismetachar(char c);

/*    parser.c    */
void	ft_parse(t_ms *ms);

//provisional structure for arguments to check the builtins



#endif
