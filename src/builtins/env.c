#include "../../inc/minishell.h"
#include "../../lib/libft/include/libft.h"

//env shows all of the enviroment variables
//STDOUT_FILENO is functionally equivalent to using the integer 1 directly
// is file descriptor for standart output.

/*typedef struct s_env
{
	char	*v_name;
    char	*v_cont;
	struct s_list	*next;
}	t_env; */

int	ft_env(t_env *env_list) //linked structure,
{
	while (env_list != NULL)
	{
		ft_putstr_fd(env_list->v_name, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putendl_fd(env_list->v_cont, STDOUT_FILENO);
		env_list = env_list->next;
	}
	return (EXIT_SUCCESS);
}

// I was writing this to test my ft_env, but also this function is to copy
// env variables and to create our list of env variables, as dup does not work 
// as I though and we have to do it manually
// this function will be at least 2 or 3 separated functions
t_env *start_env(char **env)
{
	int		i;
	int		x;
	t_env	*new_env;
	t_env	*first;
	t_env	*follow;
	
	i = 0;
	int x = 0;
	new_env = NULL;
	if (env[0] == NULL)
		return (new_env);
	new_env = malloc(sizeof(t_env) * 1);
	if (!new_env)
		return (NULL);
	first = new_env;
	while (env[i] != NULL)
	{
		follow = malloc(sizeof(t_env) * 1);
		if (!follow)
			return (NULL);
		while (env[i][k] !=)
		aux->v_name = split0;
		aux->v_cont = split1;
		new_env->next = aux;

		i++;
	}
	return new_env;
}



