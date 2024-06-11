/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:30:08 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/11 16:16:29 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//opens the filename given by the input
//saves if it's input or output
// void	handle_redir()
// {}

//Counts how many consecutive tokens of the same TYPE there are from CURRENT
//Returns COUNT
int	ft_count_toks(t_tokens *current, int type)
{
	int	count;

	count = 0;
	while (current && current->type == type)
	{
		count++;
		current = current->next;
	}
	return (count);
}

// Adds node to the end of the args list
void	add_last_arg(t_args **args, t_args *new_arg)
{
	t_args	*last;

	last = *args;
	while (last && last->next != NULL)
	{
		last = last->next;
	}
	last->next = new_arg;
	new_arg->prev = last;
}

//Creates new node for args
int	new_args_node(t_args **args, char **arr)
{
	t_args	*new_arg;
	t_args	*last;
	
	new_arg = malloc(sizeof(t_args) * 1);
	if (!new_arg)
		return(-1);	//malloc protecc
	new_arg->argv = arr;
	int i = 0;
	printf("argv[0] == %s\n", new_arg->argv[i]);
	new_arg->redir_fd = -1;
	new_arg->redir_type = -1;
	new_arg->next = NULL;
	new_arg->prev = NULL;
	if (*args == NULL)
		*args = new_arg;
	else
	{
		last = *args;
		while (last && last->next != NULL)
			last = last->next;
		new_arg->prev = last;
		last->next = new_arg;
	}
		// add_last_arg(args, new_arg);
	return (0);
}

// static void	free_str(char **arr)
// {
// 	int	j;

// 	j = 0;
// 	while (arr[j])
// 	{
// 		free(arr[j]);
// 		j++;
// 	}
// 	free (arr);
// 	return ;
// }

//Fills array arr with consecutive tokens of the same type
//Returns the array
char	**fill_arg(t_tokens **tok, t_tokens *ptr)
{
	char		**arr;
	int			arr_len;
	int			i;

	*tok = ptr;
	i = 0;
	arr_len = ft_count_toks(*tok, 0);
	arr = malloc(sizeof(char *) * (arr_len + 1));
	if (!arr)
	{
		printf("FUCK\n");
		return (NULL); //add proper handling
	}
	arr[arr_len] = NULL;
	printf("before while to fill array\n");
	while (i < arr_len)
	{
		printf("inside loop\n");
		arr[i] = ft_strdup((*tok)->tok);
		printf("arr[i] = %s, tok is = %s\n", arr[i], (*tok)->tok);
		(*tok) = (*tok)->next;
		i++;
	}
	printf("enf of fill\n");
	return (arr);
}

// //Creates nodes for t_args from t_tokens
// void	ft_prep_args(t_ms *ms)
// {
// 	t_args		*args;	//pointer to args, which is unitinialized
// 	t_tokens	*current_tok;	//pointer to toks because we dont want to lose the first position
// 	char		**arr;
	
// 	/*to fill a node of args, just ONE node, I need the array*/
// 	current_tok = ms->tokens; 
// 	args = NULL; 
// 	while (current_tok != NULL) 
// 	{
// 		if (current_tok && current_tok->type != 2)
// 		{
// 			if (current_tok->type == 0)
// 			{
// 				arr = fill_arg(current_tok);
// 				break ;
// 			}
// 			current_tok = current_tok->next;
// 		}
// 		new_args_node(&args, arr);
// 		arr = NULL;
// 		current_tok = current_tok->next;
// 	}
// 	//Test to print what's in args structure
// 	int i = 0;
// 	while (args->next != NULL)
// 	{
// 		while (args != NULL && args->argv[i] != NULL)
// 		{
// 			printf("\nStored in args:<%s>\n\n", args->argv[i]);
// 			i++;
// 		}
// 		args = args->next;
// 		printf("\n~On to next node~\n\n");
// 	}
// 	printf("%p of argv\n", args->argv[i]);
// 	while (args != NULL && args->argv[i] != NULL)
// 	{
// 		printf("\nStored in args node:<%s>\n\n", args->argv[i]);
// 		i++;
// 	}
// 	//End of test delete later
// }

// void	fun(int	**a, int *c)
// {
// 	*a = c; 
// }

// void	fun(void)
// {
// 	t_list	*a; t_tokes *a
// 	t_list	*b;
// 	t_list	*c;


// 	a = b;
// 	fun2(&a, c);
// 	print(a); == c
// }

//Creates nodes for t_args from t_tokens
void	ft_prep_args(t_ms *ms)
{
	t_args		*args;	//pointer to args, which is unitinialized
	t_tokens	*current_tok;	//pointer to toks because we dont want to lose the first position
	char		**arr;
	
	/*to fill a node of args, just ONE node, I need the array*/
	current_tok = ms->tokens; 
	args = NULL; 
	while (current_tok != NULL) 
	{
		printf("inside prep loop\n");
		while (current_tok && current_tok->type != 2)
		{
			if (current_tok->type == 0)
				arr = fill_arg(&current_tok, current_tok);
			new_args_node(&args, arr);
			arr = NULL;
		}
	}
	//Test to print what's in args structure
	int i = 0;
	printf("1\n");
	while (args->next != NULL)
	{
		printf("2\n");
		while (args != NULL && args->argv[i] != NULL)
		{
			printf("\nStored in args:<%s>\n\n", args->argv[i]);
			i++;
		}
		args = args->next;
		printf("\n~On to next node~\n\n");
	}
	printf("3\n");
	printf("%p of argv\n", args->argv[i]);
	while (args != NULL && args->argv[i] != NULL)
	{
		printf("\nStored in args node:<%s>\n\n", args->argv[i]);
		i++;
	}
	//End of test delete later
}
