/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:19:32 by dabalm            #+#    #+#             */
/*   Updated: 2023/10/07 18:16:34 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	count_words(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		while (str[i] != c && str[i])
			i++;
		count++;
	}
	if (i > 0 && str[i - 1] == c)
		count--;
	return (count);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**result;
	int		count;

	i = 0;
	count = 0;
	result = ft_calloc(count_words(s, c) + 1, sizeof(unsigned char *));
	if (!result)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		j = 0;
		while (s[i + j] != c && s[i + j])
			j++;
		if (j > 0)
		{
			result[count] = ft_substr(s, i, j);
			count++;
		}
		i += j;
	}
	return (result);
}

// void print_str_tab(char **tab)
// {
// 	int i = 0;

// 	while (tab[i])
// 	{
// 		printf("%d: %s\n", i, tab[i]);
// 		i++;
// 	}
// }
// int main(void)
// {
// 	// printf("%d\n", count_words("dit is een zin", ' '));
// 	// printf("%d\n", count_words("dit is een zin  ", ' '));
// 	// printf("%d\n", count_words("   dit is een zin", ' '));
// 	// printf("%d\n", count_words("  dit is een zin  ", ' '));
// 	// printf("%d\n", count_words("^^^1^^2a,^^^^3^^^^--h^^^^", '^'));
// 	char **splitted = ft_split("^^^1^^2a,^^^^3^^^^--h^^^^", '^');
// 	print_str_tab(splitted);
// 	int i = 0;

// 	while (splitted[i])
// 	{
// 		free (splitted[i]);
// 		i++;
// 	}
// 	free (splitted);
// }