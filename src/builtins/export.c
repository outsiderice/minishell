/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:10:49 by kkoval            #+#    #+#             */
/*   Updated: 2024/07/31 15:28:09 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

int	ft_check_export_arg(char *arg)
{
	int	i;
	int	i_plus;

	i = 0;
	i_plus = 0;
	if (ft_isalpha(arg[0]) != 1 && arg[0] != '_')
	{
		printf("eggshell: export: `%s' not a valid identifier\n", arg);
		return (-1);
	}
	while (arg[i] != '\0' && arg[i] != '=')
		i++;
	while (arg[i_plus] != '\0' && arg[i_plus] != '+')
		i_plus++;
	if (arg[i] == '=' && (i_plus + 1 >= i))
		return (0);
	else
		printf("eggshell: export: `%s' not a valid identifier\n", arg);
	return (-1);
}

//ADD ARGUMENT TO ENV
int	ft_add_to_env(t_env *env_list, char *arg)
{
	t_env	*aux;
	t_env	*node;

	aux = NULL;
	//if (env_list == NULL) se tiene que gestionar fuera
		//return (-1);
	node = malloc(sizeof(t_env) * 1);
	if (!node)
		return (-1);
	if (ft_assign(arg, &node) == -1)
		return (-1);
	while (env_list->next != NULL)
	{
		if (ft_str_compare(env_list->v_name, node->v_name) == 0)
			aux = env_list;
		env_list = env_list->next;
	}
	if (ft_str_compare(env_list->v_name, node->v_name) == 0)
		aux = env_list;
	if (aux == NULL)
	{
		aux = malloc(sizeof(t_env) * 1);
		if (!aux)
			return (-1);
		aux->v_name = ft_strdup(node->v_name);
		aux->next = NULL;
		env_list->next = aux;
	}
	aux->v_cont = ft_strdup(node->v_cont);
	//printf("New env var added: %s = %s\n", aux->v_name, aux->v_cont );
	free(node);
	return (1);
}

int	*ft_sort_alpha(char **env, int len)
{
	int		i;
	int		x;
	int		*ind;
	int		pos;

	if (len == 0)
		return (NULL);
	ind = malloc(sizeof(int) * len);
	if (!ind)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		x = 0;
		pos = 0;
		while (env[x] != NULL)
		{
			if (ft_strcmp(env[i], env[x]) > 0)
				++pos;
			x++;
		}
		ind[i] = pos;
		i++;
	}
	return (ind);
}

// NO ARGUMENTS, ONLY PRINT ENV_LIST
void	ft_export_no_args(t_env *env_list, int fd)
{
	char	**env;
	t_env	*first;
	int		*ind;
	int		i;
	int		j;

	first = env_list;
	env = ft_list_to_array(env_list);
	i = 0;
	ind = ft_sort_alpha(env, ft_lstlen(env_list));
	while (i < ft_lstlen(env_list))
	{
		j = -1;
		while (ind[++j] != i)
			env_list = env_list->next;
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(env_list->v_name, fd);
		ft_putchar_fd('=', fd);
		ft_putchar_fd('"', fd);
		ft_putstr_fd(env_list->v_cont, fd);
		ft_putendl_fd("\"", fd);
		env_list = first;
		i++;
	}
	return ;
}

// CONTROL FUNCTION, CHOOSES THE RIGHT CASE FOR EXPORT
int	ft_export(t_ms *ms, char **args, int fd)
{
	int	res;

	res = 0;
	args++;
	if (*args == NULL)
		ft_export_no_args(ms->env, fd);
	else
	{
		while (*args != NULL)
		{
			if (ft_check_export_arg(*args) == 0)
			{
				ft_add_to_env(ms->env, *args);
			}
			else
				res = 1;
			args++;
		}
	}
	return (res);
}
