/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:27:10 by kkoval            #+#    #+#             */
/*   Updated: 2024/05/29 15:27:18 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../inc/minishell.h"
#include <unistd.h>
#include <stdio.h>

// this functions compares without a need of strlen
int ft_str_compare(char *str1, char *str2)
{
    int i;
    
	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (1);
		i++;
	}
	if (str1[i] == '\0' && str2[i] == '\0')
        return (0);
	return (1);
}

/*int main(void)
{
	printf("%d\n", ft_str_compare("", ""));
	return (0);
}*/