/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:34:18 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/20 09:34:26 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../lib/libft/include/libft.h"
#include <unistd.h>
#include <stdio.h>

/*  FT_PWD
	This function should receive main struct as a parameter,
	but as we do not have it now I decide to mantain it void by now.
	Also, it should change the exit status in the main struct. 
*/

/*  char *getcwd(char *buf, size_t size);
	Parameters:
	1. buf: a pointer to a buffer where the current working directory path will be stored. 
	If buf is NULL, getcwd will allocate the buffer itself.
	2. size: The size of the buffer. If buf is NULL, this parameter specifies the number of 
	bytes to allocate for the buffer.
	Returns:
	On success: a pointer to the buffer containing the current working directory path.
	On failure: eeturns NULL and sets errno to indicate the error.
	!! It is necessary to free allocated memory.
*/
void	ft_pwd(void)
{
	char	*pwd;

	//mini_shell->exit_status = 0;
	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		ft_putendl_fd(pwd, STDOUT_FILENO);
		free(pwd);
	}
	else
	{
		printf("error pwd");
		// handle better this error, maybe perror?
	}
}

/*
int	main(void)
{
	ft_pwd();
	return (1);
}*/
