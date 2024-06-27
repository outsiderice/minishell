#include "../inc/minishell.h"

void	prep_redir(t_tokens *tok, t_args *args)
{
	if (tok->tok[0] == '<')
	{
		if (ft_strlen(tok->tok == 1))
			args->redir_type = 1;
		else
			args->redir_type = 2;
	}
	if (tok->tok[0] == '>')
	{
		if (ft_strlen(tok->tok == 1))
			args->redir_type = 3;
		else
			args->redir_type = 4;
	}
}