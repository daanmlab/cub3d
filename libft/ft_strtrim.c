/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 20:17:39 by dabalm            #+#    #+#             */
/*   Updated: 2023/10/07 18:16:04 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_contains(char const *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

// 0 = len; 1 = start; 2 = end; 3 = i
char	*ft_strtrim(char const *s1, char const *set)
{
	int		i[4];
	char	*result;

	i[0] = ft_strlen((char *)s1);
	i[1] = 0;
	while (ft_contains(set, s1[i[1]]))
		i[1]++;
	i[2] = 1;
	while (ft_contains(set, s1[i[0] - i[2]]))
		i[2]++;
	i[2]--;
	if (i[1] + i[2] >= i[0])
		return (ft_calloc(1, sizeof(char)));
	result = ft_calloc((i[0] - (i[1] + i[2])) + 1, sizeof(char));
	if (!result)
		return (NULL);
	i[3] = 0;
	while (i[1] + i[3] < i[0] - i[2])
	{
		result[i[3]] = s1[i[1] + i[3]];
		i[3]++;
	}
	result[i[3]] = '\0';
	return (result);
}

// #include <stdio.h>
// int main(void)
// {
//     char *test = "=-=-=+_++_+_abcdefg=-=+_=-+_=-+_+_=";
//     char *result = ft_strtrim(test, "-_=+");
//     printf("%s", result);
// }
