/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:22:05 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/14 14:41:27 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//echo -n "hola" "hola"

void	ft_echo(char **str)
{
	int	i;

	i = 1;
	if (ft_strncmp(*str[0], "-n", 2) == 0 && ft_strlen(str[0]) == 2)
		while (**str)
		{
			ft_printf("%s", str[i]);
			i++;
		}
	else
	{
		while (**str)
		{
			ft_printf("%s", str[i]);
			i++;
		}
		ft_printf("\n");
	}
	return ;
}



probando merging

hello
// int	main(int argc, char **argv)
// {
// 	ft_echo(argv);
// }