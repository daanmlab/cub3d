/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:41:17 by dabalm            #+#    #+#             */
/*   Updated: 2023/10/04 18:27:04 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int	i;
	int	j;

	i = 0;
	if (ft_strlen((char *)little) == 0)
		return ((char *)big);
	while (big[i] && (i < (int)len || (int)len == -1))
	{
		j = 0;
		while (big[i + j] == little[j] && big[i + j] && ((i + j) < (int)len
				|| (int)len == -1))
			j++;
		if (little[j] == '\0')
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// int main(void)
// {
// 	printf("%s\n", strnstr("alright then", "then", 13));
// 	printf("%s\n", strnstr("alright then", "", 13));
// 	printf("%s\n", strnstr("", "then", 13));
// }
