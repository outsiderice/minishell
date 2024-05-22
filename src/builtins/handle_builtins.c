#include "../../inc/minishell.h"
#include "../../lib/libft/include/libft.h"

// I think this it a necessary controler file that would call other builtin functions,
// as some of them need more arguments than others. So this one would receive all the possible arguments needed.
// As the structure is still not clear, we will see later how exactly we can hanfle it.
// So far I understand there is going to be a structure that would have inside the number or code name 
// to determinate if it should call builtin or command, in case of a built-in it would end here, and from here
// 1 of the 7 built-in functions would be called.
// Some of them require more arguments then others.


//this function has to return some sort of value for control check purposes or not :)
int	handle_builtins()
{
	

}
/*
ft_buliting(t_tokens **tokens)
{
    t_tokens *current;

    if (current->token ftstrncompare(echo) && strlen)
    ft_echo
    {
        *current


    }
}
*/
