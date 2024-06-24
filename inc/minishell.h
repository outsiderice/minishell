/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:40:16 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/24 16:09:52 by amagnell         ###   ########.fr       */
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
	int				redir_type; //<, <<, > and >> are different, -1 for empty
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
char	**ft_list_to_array(t_env *env);

/*    signals.c    */

/*    get_input.c    */
char	*ft_readline(void);

/*    error.c    */
// void	ft_error(t_ms **ms, char *line);
int		error_msg(char *msg, char *deets);

/*    check_quotes.c    */
int		ft_check_quotes(const char *line, t_ms *ms);
int		ft_quote_len(const char *line, char type);

/*    tokenize.c    */
int		ft_tok_checks(const char *line, t_ms *ms);
// void		ft_get_toks(const char *line, t_tokens **tokens);

/*    token_utils.c    */
int		ft_ismetachar(char c);
int		ft_space_len(const char *line);
int		ft_isoperator(const char *line);
int		ft_isword(const char *line);

/*    tokens_lst_utils.c    */
int		ft_addtok(const char *line, int len, int type, t_tokens **tokens);
// void	ft_tok_addback(t_tokens **tokens, t_tokens *new_tok);
// void	del_tok(t_tokens **lst, t_tokens *tok);

/*    parser.c    */
int		ft_parse(t_ms *ms);

/*    expand.c    */
int		expand_quotes(t_tokens *tok);
int		is_expandable_dollar(t_ms *ms, t_tokens *tok);
int		find_dollar_end(const char *name);
char	*add_shit(char	*str, char *src, int *ptr);

/*    expand_utils.c   */
char	*rm_delimiters(char *tok, int *i);
char	*append_end(char *start, char *original, int i);

/*    prep_execution.c    */
void	ft_prep_args(t_ms *ms);

/*    execution.c    */
void	exeggutor(t_ms *ms);

/*    exec_prototype.c    */
int		ft_exec(t_ms *ms);

/*    handle_builtins.c    */
int		is_builtin(char *cmd);
int		handle_builtins(t_ms *ms);
// int	ft_echo(char **args);
int		ft_pwd(void);
int		ft_env(t_env *env_list);
// int	ft_export(t_env *env_list, t_args *args_list);
// int ft_unset(t_env **env, t_args *args);

/*    builtins_utils.c    */
int		ft_str_compare(char *str1, char *str2);

#endif