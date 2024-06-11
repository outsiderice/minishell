/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:04:18 by kkoval            #+#    #+#             */
/*   Updated: 2024/06/11 16:49:40 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* DESCRIPTION FROM SHELL MANUAL
	Change the current working directory to directory. If directory is not supplied, the value of the HOME shell variable is used. If the shell variable CDPATH exists, 
	it is used as a search path: each directory name in CDPATH is searched for directory, with alternative directory names in CDPATH separated by a colon (‘:’). 
	If directory begins with a slash, CDPATH is not used.
*/

/* How cd should behave:
1. cd with no arguments => NOT ASKED IN EVAL SHEET
	1. should go to HOME path (HOME env variable)
	2. should change it's current PWD (to HOME path) and OLDPWD(will reflect it's previous PWD)
2. cd ..
	1. goes to previous directory
	2. changes PWD and OLDPWD
3. cd relative path should not start with /
4. cd absolut path should start with /
5. cd . => we remain in the same directory, however the OLDPWD is changed to current PWD
5. DOUBTS:
	1. Should we impliment cd with no arguments? Some projects have it, but it is not specified in PDF
	2. Do we have to check permissions to enter specific directories?
	3. How to check if the directory exists? 
	4. How far can we cd back? -- Should not cd more that to \
*/

//To list the directories (or files) 
//in a directory in C, you can use the POSIX opendir, readdir, and closedir functions, which are part of the dirent.h


int	ft_cd(t_ms *ms, t_args *args)
{
	char	*path; // line that will retain the path to go

	path = NULL;
	if (args == NULL)
		return (ft_cd_no_arg(ms));
	// if argument is = . should give error because the permission is denied -> check access
	else 
	{


	}	
	if (pwd != NULL)
	{
		ft_putendl_fd(pwd, STDOUT_FILENO);
		free(pwd);
		return (0); //or save exit status in mini_shell->exit_status = 0;
	}
	if (m_sh->comand_arg > 2) // args control;  
		retunr(printf("error message, too many arguments\n")); // adjust the message
	
}

int	ft_cd_no_arg(t_struct *ms)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (1);
	// if old_pwd is not NULL, should we free it first?
	ms->old_pwd = *path; // should it be malloc instead?
	free(path);
	return (0);
} 




/* FUNCTION PROTOTYPES
	1. int chdir(const char *path) is used to change the current working directory of the calling process.
	Parameter:
		 A pointer to a string that specifies the path to the new working directory.
	Return Value:
		On success, chdir returns 0.
		On failure, it returns -1 and sets the errno variable to indicate the error.
	Common Error Codes
		ENOENT: The directory specified by path does not exist.
		EACCES: Permission is denied to change to the specified directory.
		ENOTDIR: A component of the path is not a directory.
*/

