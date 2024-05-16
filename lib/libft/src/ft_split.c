/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:23:50 by amagnell          #+#    #+#             */
/*   Updated: 2024/05/16 17:52:47 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
# include "../../../inc/lexer.h"
# include "../../../inc/check_input.h"


//splits string s into an array of strings using char c as a delimiter.
//Array ends with a NULL pointer.

static int	count_words(char const *s, int c)
{
	int	i;
	int	wordcount;
	int	a;

	a = -1;
	wordcount = 0;
	i = 0;
	ft_printf("in split, s is %s\n", s); //test
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			i = i + ft_quote_len(&s[i], s[i]);
		if (s[i] == c)
			a = -1;
		if (s[i] != c && a == -1)
		{
			a = 1;
			wordcount++;
		}
		i++;
	}
	ft_printf("wordcount is %d\n", wordcount); //test
	return (wordcount);
}

static void	free_str(char **arr)
{
	int	j;

	j = 0;
	while (arr[j])
	{
		free(arr[j]);
		j++;
	}
	free (arr);
	return ;
}

static char	**fill_arr(char **arr, char const *s, char c)
{
	unsigned int	start;
	int				i;
	int				j;

	j = 0;
	i = -1;
	start = 0;
	while (s[++i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			arr[j] = ft_substr(s, start, i - start + 1);
			if (!arr[j])
			{
				free_str(arr);
				return (NULL);
			}
			j++;
		}
		if (s[i] == c && s[i + 1] && s[i + 1] != c)
			start = i + 1;
	}
	arr[j] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;

	arr = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!arr)
		return (NULL);
	ft_printf("before fill\n"); //test
	arr = fill_arr(arr, s, c);
	ft_printf("end of split\n"); //test
	return (arr);
}
