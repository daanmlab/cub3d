/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:31:48 by dabalm            #+#    #+#             */
/*   Updated: 2023/10/04 18:28:14 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen((char *)src));
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen((char *)src));
}

// #include <stdio.h>
// #include "./ft_strlen.c"
// #include <bsd/string.h>
// int main(void)
// {
// 	char dest1[] = "yeayea";
// 	char dest2[] = "yeayea";
// 	char src[] = "nonono";
// 	printf("%zu\n", ft_strlcpy(dest1, src, 7));
// 	printf("%s\n", dest1);
// 	printf("%zu\n", strlcpy(dest2, src, 7));
// 	printf("%s\n", dest2);
// }