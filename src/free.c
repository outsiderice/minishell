/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:24:15 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/07 16:05:32 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node(t_env *env)
{
	if (env->v_name != NULL)
		free(env->v_name);
	if (env->v_cont != NULL)
		free(env->v_cont);
	if (env != NULL)
		free(env);
}

void	free_int_ptr(int *ptr)
{
	if (ptr != NULL)
		free(ptr);
}

void	free_double_int_ptr(int **ptr, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free_int_ptr(ptr[i]);
		i++;
	}
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	free_env(t_env **env)
{
	t_env	*current;
	t_env	*aux;

	current = *env;
	while (current != NULL)
	{
		aux = current;
		free(current->v_name);
		if (current->v_cont)
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
		if (tok->tok)
			free(tok->tok);
		tok = tok->next;
		free(tmp_tok);
	}
	*toks = NULL;
	while (arg != NULL)
	{
		tmp_arg = arg;
		if (arg->argv)
			free_arr(arg->argv);
		arg = arg->next;
		free(tmp_arg);
	}
	*args = NULL;
}

//GLOBAL T_MS FREE
void	free_ms(t_ms **ms)
{
	free_env(&(*ms)->env);
	free_tok_and_args(&(*ms)->tokens, &(*ms)->args);
	// if ((*ms)->pwd != NULL)
	// 	free((*ms)->pwd);
	// if ((*ms)->old_pwd != NULL)
	// 	free((*ms)->old_pwd);
	free((*ms)->pid);
	(*ms)->pid = NULL;
	//free_int_ptr((*ms)->pid);
	//free_double_int_ptr((*ms)->pipes, (*ms)->cmnds_num);
} 
