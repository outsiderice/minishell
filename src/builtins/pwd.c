/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:58:24 by kkoval            #+#    #+#             */
/*   Updated: 2024/07/03 15:58:35 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../inc/minishell.h"

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

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		ft_putendl_fd(pwd, STDOUT_FILENO);
		free(pwd);
		return (0); //or save exit status in mini_shell->exit_status = 0;
	}
	else
	{
		printf("error pwd");// handle better this error, maybe perror?
		return (1);
	}
}

/*
int	main(void)
{
	printf("%d\n", ft_pwd());
	return (1);
}*/