//#include "../inc/minishell.h"
//#include "../../lib/libft/include/libft.h"
#include <stdio.h>

int is_numeric(char *str) 
{
    if (!str || *str == '\0')
        return (0);
    if (*str == '-' || *str == '+')
        str++;
    while (*str) 
	{
        if (*str < '0' || *str > '9') 
            return (0);
        str++;
    }
    return (1);
}

/*int	main(void)
{
Test 1: 12345 is numeric
Test 2: -6789 is numeric
Test 3: 12a45 is not numeric
Test 4:  is not numeric
Test 5: +123 is numeric
Test 6: 0 is numeric
Test 7: -0 is numeric
Test 8: ' 123' is not numeric
Converted number from test1: 12345
Converted number from test2: -6789
Converted number from test5: 123

	printf("%d\n", is_numeric("12345"));
	printf("%d\n", is_numeric("-6789"));
	printf("%d\n", is_numeric("12a45"));
	printf("%d\n", is_numeric(""));
	printf("%d\n", is_numeric("+123"));
	printf("%d\n", is_numeric("0"));
	printf("%d\n", is_numeric("-0"));
	printf("%d\n", is_numeric(" 123"));

	return (0);
}*/