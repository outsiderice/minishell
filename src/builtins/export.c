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
