#include "../../inc/minishell.h"
#include "../../lib/libft/include/libft.h"

/* EXPORT
	1. This built-in saves variables passed as enviroment variables if has specific arfument
		NAME=VALUE -> no space between name and value 
	2. export with no arguments
		bash-3.2$ export
		declare -x HOME="/Users/kate"
		declare -x HOMEBREW_CELLAR="/opt/homebrew/Cellar"
		declare -x HOMEBREW_PREFIX="/opt/homebrew"
		declare -x HOMEBREW_REPOSITORY="/opt/homebrew"
		declare -x INFOPATH="/opt/homebrew/share/info:"
		etc... until the end of env list.
*/

/* TO DO: 
	1. Function: Parsing to see if it fits the standart to add it to the list on env variables.
	2. Function: if it does fit add it to env list.
	3. Function: if export has no arguments to go through env list and print it in this structure:
		declare -x HOME="/Users/kate"
		declare -x HOMEBREW_CELLAR="/opt/homebrew/Cellar"
		etc...
*/

/*A parameter is an entity that stores values. It can be a name, a number, or one of the special characters listed below. A variable is a parameter denoted by a name. 
A variable has a value and zero or more attributes. Attributes are assigned using the declare builtin command (see the description of the declare builtin in Bash Builtin Commands).
A parameter is set if it has been assigned a value. The null string is a valid value. Once a variable is set, it may be unset only by using the unset builtin command.

A variable may be assigned to by a statement of the form

name=[value]
If value is not given, the variable is assigned the null string. All values undergo tilde expansion, parameter and variable expansion, command substitution, 
arithmetic expansion, and quote removal (see Shell Parameter Expansion). If the variable has its integer attribute set, then value is evaluated as an 
arithmetic expression even if the $((…)) expansion is not used (see Arithmetic Expansion). Word splitting and filename expansion are not performed. 
Assignment statements may also appear as arguments to the alias, declare, typeset, export, readonly, and local builtin commands (declaration commands). 
When in POSIX mode (see 
Bash POSIX Mode), these builtins may appear in a command after one or more instances of the command builtin and retain these assignment statement properties.*/

//FUNCTION TO CHECK IF IT SHOULD BE STORRED

//EXPORT WITH NO ARGUMENTS -> declare -x VARIABLE_NAME="value"\n in alphabetical order si quieres
/*
typedef struct s_env
{
	char			*v_name;
	char			*v_cont;
	struct s_env	*next;
}	t_env;

//provisional structure for arguments to check the builtins

typedef struct s_args
{
	char			*arg;
	struct s_args	*next;
}	t_args;
*/

//CHECKS THE VALIDITY OF ARGUMENT TO BE ADDED 

int		ft_check_export_arg(t_args *args_list)
{
	//NAME
	// =
	// VALUE, if no value saves "\0"
}

//ADD ARGUMENT TO ENV

void	ft_add_to_env(t_env *env_list, t_args *args)
{
	
	if (env_list == NULL);
	{
		//create the structure
	}
	else
	{
		while ()
	}
}

// NO ARGUMENTS, ONLY PRINT ENV_LIST
void	ft_export_no_args(t_env *env_list)
{
	while (env_list != NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env_list->v_name, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putendl_fd(env_list->v_cont, STDOUT_FILENO);
		env_list = env_list->next;
	}
	return;
}

// CONTROL FUNCTION HAS TO RETURN 0 or 1
int	ft_export(t_env *env_list, t_args *args_list) //chekea las opciones no argummentos
{
	if (args_list->next == NULL)
		ft_export_no_args(env_list);
	else
	{
		args_list = args_list->next;
		while (args_list != NULL)
		{
			//check arguments and if they pass (ft_check_arg == 0) add them to env_list
			if (ft_check_export_arg == 0)
			{
				//function add arg to env_list
				ft_add_to_env(env_list, args_list);
			}
			args_list = args_list->next;
		}

	}
	//free the args ft_free_tokens

}
