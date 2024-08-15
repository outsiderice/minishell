/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:49:12 by kkoval            #+#    #+#             */
/*   Updated: 2024/08/09 19:45:09 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_print_env(t_env *env_list, int fd)
{
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(env_list->v_name, fd);
	ft_putchar_fd('=', fd);
	ft_putchar_fd('"', fd);
	ft_putstr_fd(env_list->v_cont, fd);
	ft_putendl_fd("\"", fd);
	return ;
}

int	is_var_in_list(t_env *env_list, char *name)
{
	while (env_list != NULL)
	{
		if (ft_str_compare(env_list->v_name, name) == 0)
			return (0);
		env_list = env_list->next;
	}
	return (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int				i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	i = 0;
	while (ptr1[i] && ptr2[i] && ptr1[i] == ptr2[i])
		i++;
	if (ptr1[i] == '\0' && ptr2[i] != '\0')
		return (-1);
	else if (ptr1[i] != '\0' && ptr2[i] == '\0')
		return (1);
	else if (ptr1[i] == '\0' && ptr2[i] == '\0')
		return (0);
	return (ptr1[i] - ptr2[i]);
}
