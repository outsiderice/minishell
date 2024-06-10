/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:40:16 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/10 16:17:48 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*    LIBRARIES    */
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include "../lib/readline/readline.h"
# include "../lib/readline/history.h"
# include "../lib/libft/include/libft.h"

/*    STRUCTURES    */
//type 0 = word, quoted or unquoted
//type 1 = filename preceded by a redirection
//type 2 = operator, a pipe
//type 3 = operator, a redirection
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

typedef struct s_args
{
	int				fd[2]; // for pipe
	int				redir_fd; // fd of file opened for redirection
	int				redir_type; //each type, <, <<, > and >> are a different number, no redir is -1
	char			**argv;
	struct s_args	*next;
	struct s_args	*prev;
}	t_args;

typedef struct s_ms
{
	t_env		*env;
	t_tokens	*tokens;
	t_args		*args;
	char		**envp;
	int			exitstatus;
	int			sh_lvl;
	char		*new_pwd;
	char		*old_pwd;
	int			pid;
}	t_ms;

/*    main.c    */
void	ft_minishell(t_ms *ms);

/*    environment.c   */		//to initialize t_env
t_env	*start_env(char **env_p);
char 	**ft_list_to_array(t_env *env);

/*    signals.c    */

/*    get_input.c    */
char	*ft_readline(void);

/*    error.c    */
void	ft_error(t_ms **ms, char *line);

/*    check_quotes.c    */
int		ft_check_quotes(const char *line, t_ms *ms);
int		ft_quote_len(const char *line, char type);

/*    tokenize.c    */
int		ft_tokenize(const char *line, t_ms *ms);
// void		ft_get_toks(const char *line, t_tokens **tokens);

/*    token_utils.c    */
int		ft_ismetachar(char c);
int		ft_space_len(const char *line);
int		ft_isoperator(const char *line);
int		ft_isword(const char *line);

/*    tokens_lst_utils.c    */
void	ft_addtok(const char *line, int len, int type, t_tokens **tokens);
// void	ft_tok_addback(t_tokens **tokens, t_tokens *new_tok);

/*    parser.c    */
void	ft_parse(t_ms *ms);

/*    expand.c    */
void	ft_expansion_check(t_ms *ms);

/*    prep_execution.c    */
void	ft_prep_args(t_ms *ms);

/*    execution.c    */
void	exeggutor(t_ms *ms);

/*    handle_builtins.c    */


/*    builtins_utils.c    */
int ft_str_compare(char *str1, char *str2);

#endif