/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:30:50 by amagnell          #+#    #+#             */
/*   Updated: 2024/06/30 17:30:03 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	prep_redir(t_tokens **tok, t_args *args)
{
	if ((*tok)->tok[0] == '<')
	{
		if (ft_strlen((*tok)->tok) == 1)
			args->redir_type = 1;
		else
			args->redir_type = 2;
	}
	else if ((*tok)->tok[0] == '>')
	{
		if (ft_strlen((*tok)->tok) == 1)
			args->redir_type = 3;
		else
			args->redir_type = 4;
	}
	else if ((*tok)->type == 1)
	{
		args->filename = ft_strdup((*tok)->tok);
		if (!args->filename)
			return (EXIT_FAILURE);
	}
	(*tok) = (*tok)->next;
	return(EXIT_SUCCESS);
}

void	free_arr(char **arr)
{
	int	j;

	j = 0;
	while (arr[j])
	{
		free(arr[j]);
		j++;
	}
	free (arr);
	return ;
}
