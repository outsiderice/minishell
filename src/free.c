/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:24:15 by amagnell          #+#    #+#             */
/*   Updated: 2024/07/18 18:19:00 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env **env)
{
	t_env	*current;
	t_env	*aux;

	current = *env;
	while (current != NULL)
	{
		aux = current;
		free(current->v_name);
		free(current->v_cont);
		current = current->next;
		free(aux);
	}
	*env = NULL;
}



void	free_tok_and_args(t_tokens **toks, t_args **args)
{
	t_tokens	*tok;
	t_tokens	*tmp_tok;
	t_args		*arg;
	t_args		*tmp_arg;

	tok = *toks;
	arg = *args;
	while (tok != NULL)
	{
		tmp_tok = tok;
		free(tok->tok);
		tok = tok->next;
		free(tmp_tok);
	}
	*toks = NULL;
	while (arg != NULL)
	{
		tmp_arg = arg;
		free_arr(arg->argv);
		arg = arg->next;
		free(tmp_arg);
	}
	*args = NULL;
}
