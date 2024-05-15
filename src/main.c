/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:29:38 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/15 17:11:39 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_readline(void)
{
	char	*line;
	char	*prompt;

	prompt = "eggshell~$";
	line = readline(prompt);
	if (!line)
		exit(EXIT_FAILURE);
	if (line)
		add_history(line);
	return (line);
}

//posicion *line y tambien si es ' o " 
//iterar sobre la line hasta econtrar una del mismo que la cierre 
//si la encuentra bien y tenemos que guardar 1 la posicion y el len incluyendo la comilla final
// y si no mensaje de error
int	ft_quotes(char *line, char type, int start)
{
	int	i;

	i = 0;
	start++;
	while (line[start] && line[start] != type)
	{
		start++;
		i++;
	}
	if (line[start] == type)
	{
		i++;
		return (i);
	}
	ft_printf("error\n");
	exit (EXIT_FAILURE);
}

int	ft_check_input(char *line)
{
	int	i;
	int	qt_len;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			qt_len = ft_quotes(&line[i], line[i], i);
			ft_printf("qt len is %d\n", qt_len);
			i = i + qt_len;
		}
		i++;
	}
	return (0);
}

void	ft_minishell(char **env)
{
	(void)env;
	char	*line;

	line = NULL;
	while (2)
	{
		line = ft_readline();
		ft_check_input(line);
		free (line);
	}
	return ;
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	if (argc != 1)
		return (EXIT_FAILURE);
	ft_minishell(env);
	return (0);
}
