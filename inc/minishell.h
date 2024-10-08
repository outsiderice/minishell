/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:40:16 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/12 15:13:56 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*    LIBRARIES    */
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "../lib/readline/readline.h"
# include "../lib/readline/history.h"
# include "../lib/libft/libft.h"

extern int	g_signstat;

/*    STRUCTURES    */
//type 0 = word, quoted or unquoted
//type 1 = filename preceded by a redirection
//type 2 = operator, a pipe
//type 3 = operator, a redirection
//type 4 = heredoc operator
//type 5 = EOF
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
	int				fd[2];
	int				redir_type;
	char			*o_file;
	char			*i_file;
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
	char		*pwd;
	char		*old_pwd;
	int			*pid;
	int			**pipes;
	int			cmnds_num;
	int			heredoc;	
}	t_ms;

/*    main.c    */
void	ft_minishell(t_ms *ms);

/*    environment.c   */		//to initialize t_env
t_env	*start_env(char **env_p);
char	**ft_list_to_array(t_env *env);
int		ft_get_shll_lvl(t_env *env);
int		ft_assign(char *env_p, t_env **current);
int		ft_lstlen(t_env *env);
int		ft_set_shll_lvl(t_env *env);

/*   env_utils.c   */
char	*get_var_name(char *str, int start);
t_env	*find_env_var(t_env *env, char *var_name);

/*    signals.c    */
void	ft_start_signals(int mode);
void	ft_ignoresig(int signal);

/*    get_input.c    */
char	*ft_readline(t_ms *ms, const char *prompt);

/*    error.c    */
// void	ft_error(t_ms **ms, char *line);
int		error_msg(char *msg, char *deets);
int		error_msg2(char *msg, char *deets, char *deets2, int nl);

/*    free.c    */
void	free_env(t_env **env);
void	free_int_ptr(int **ptr);
void	free_tok_and_args(t_tokens **toks, t_args **args);

/*    heredoc.c    */
int		handle_heredocs(t_ms *ms);

/*    heredoc_expansion.c    */
char	*expand_line(t_ms *ms, t_env *env_var, char *line);

/*    prep_execution.c    */
int		ft_prep_args(t_ms *ms);

/*    open.c    */
void	open_input(char *tok, char *file, t_args *args, t_ms *ms);
void	open_output(char *tok, char *file, t_args *args);

/*    prep_utils.c    */
void	free_arr(char **arr);
int		new_args_node(t_args **args);
int		ft_count_toks(t_tokens *current, int type);

/*---------------------------------------------*/
/*               EXECUTION                     */
/*---------------------------------------------*/
/*              execution.c                    */
void	exeggutor(t_ms *ms);

/*              exec_1.c                       */
void	create_forks(t_ms *ms, t_args *args, int i);
void	ft_exec_builtin(t_ms *ms, t_args *args, int i);

/*              exec_path.c                    */
int		is_file_in_dir(char *file, char *dir);
char	**ft_get_paths(t_env *env);
char	*ft_find_path(char *file, char **paths);
char	*ft_join_path(char *path, char *cmd);
int		check_access(t_ms *ms, char *file);

/*               exec_utils.c                   */
int		ft_t_args_len(t_args *args);
void	ft_close_fd(t_args *args);
void	close_pipes(int **pipes, int first, int last, int len);
int		handle_pipes(t_ms *ms);
int		handle_pids(t_ms *ms);

/*---------------------------------------------*/
/*               PARSING                       */
/*---------------------------------------------*/
/*    check_quotes.c    */
int		ft_check_quotes(const char *line, t_ms *ms);
int		ft_quote_len(const char *line, char type);

/*    expand_utils.c   */
char	*rm_delimiters(char *tok, int i);
char	*all_join(char *s1, char *s2, char *s3);
char	*get_dollar_content(t_ms *ms, t_env *env, char *var_name);
int	no_expansion(t_tokens *token, char *tok, int i);
// int		find_dollar_end(const char *name);

/*    env_utils.c    */
t_env	*find_env_var(t_env *env, char *var_name);
char	*get_var_name(char *str, int start);
int		ft_retokenize(t_tokens *tok, int i, char *content, int v);

/*    expand.c    */
int		expand_quotes(t_tokens *tok);
int		is_expandable_dollar(t_ms *ms, t_tokens *tok);

/*    parser.c    */
int		ft_parse(t_ms *ms);

/*    token_utils.c    */
int		ft_ismetachar(char c);
int		ft_space_len(const char *line);
int		ft_isoperator(const char *line);
int		ft_isword(const char *line);

/*    tokenize.c    */
int		ft_tok_checks(const char *line, t_ms *ms);
// void		ft_get_toks(const char *line, t_tokens **tokens);

/*    tokens_lst_utils.c    */
int		ft_addtok(const char *line, int len, int type, t_tokens **tokens);
void	free_toks(t_tokens **toks);
// void	ft_tok_addback(t_tokens **tokens, t_tokens *new_tok);

/*---------------------------------------------*/
/*               BUILTINS                      */
/*---------------------------------------------*/
/*    handle_builtins.c    */
int		is_builtin(char *cmd);
int		handle_builtins(t_ms *ms, t_args *args, int fd);
int		ft_echo(t_args *args, int fd);
int		ft_pwd(int fd);
int		ft_env(t_args *args, t_env *env_list, int fd);
int		ft_export(t_ms *ms, char **args, int fd);
int		is_numeric(char *str);
int		ft_exit(t_ms *ms, char **args);
int		ft_cd(t_ms *ms, char **args, int fd);
int		ft_unset(t_ms *ms, char **args);

/*    builtins_utils.c    */
int		ft_str_compare(char *str1, char *str2);
char	*get_env_cont(t_env *env, char *str);
int		ft_args_len(char **args);
int		ft_set_env_cont(t_env *env, char *name, char *cont);
int		*ft_sort_alpha(char **env, int len);

/*    export_utils.c                           */
void	ft_print_env(t_env *env_list, int fd);
int		is_var_in_list(t_env *env_list, char *name);
int		ft_strcmp(const char *s1, const char *s2);

/*---------------------------------------------*/
/*                   FREE                      */
/*---------------------------------------------*/
void	free_node(t_env *env);
void	free_ms(t_ms **ms);
void	free_char_ptr(char *ptr);
#endif