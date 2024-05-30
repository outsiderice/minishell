/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:08:33 by kkoval            #+#    #+#             */
/*   Updated: 2024/05/30 16:45:51 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//it assigns names and values to the nodes
int		ft_assig(char *env, t_env **current)
{
	int		equal;
	char	*equal_ptr;
	int		env_len;

	if(*env == NULL) //Error, nothing to save
		return (-1);
	equal_ptr = ft_strchr(*env, '=');
	if (equal_ptr == NULL) //Error
		return (-1);
	env_len = ft_strlen(env);
	equal_position = equal_position - env;
	

	 





	while(*env != NULL)
	{

	}
}

t_env	*start_env(char **env_p)
{
    int		i;
    t_env	*first;
    t_env	*current;
    
    first = NULL;
    current = NULL;
	while (env_p[i] != NULL)
	{


	}
    
	
	
	if (env_p == NULL || env[0] == NULL)
        return (NULL);

}




int	main(int ac, char **av, char **envp)
{
    t_env	*env;
    t_env	*

    env = start_env(envp);
    return (0);
}