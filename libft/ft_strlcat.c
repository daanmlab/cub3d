/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:31:48 by dabalm            #+#    #+#             */
/*   Updated: 2023/10/04 18:34:41 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	int		dst_size;

	dst_size = ft_strlen(dst);
	if (size == 0)
		return (ft_strlen((char *)src));
	i = 0;
	while (src[i] && (((i + dst_size) < (size - 1)) || (int)size == -1))
	{
		dst[i + dst_size] = src[i];
		i++;
	}
	dst[dst_size + i] = '\0';
	if ((int)size == -1)
		return (i + dst_size);
	if (dst_size < (int)size)
	{
		return (ft_strlen((char *)src) + dst_size);
	}
	return (ft_strlen((char *)src) + (int)size);
}

// #include <stdio.h>
// #include <bsd/string.h>
// int main(void)
// {
// 	char dest1[20] = "yeayea";
// 	// char dest2[20] = "yeayea";
// 	int  n = -1;
// 	char src[] = "nonono";
// 	printf("%zu\n", ft_strlcat(dest1, src, n));
// 	printf("%s\n", dest1);
// 	// printf("%zu\n", strlcat(dest2, src, n));
// 	// printf("%s\n", dest2);
// }