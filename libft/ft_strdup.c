/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:14:08 by dabalm            #+#    #+#             */
/*   Updated: 2023/10/04 12:36:37 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(char *src)
{
	char	*dest;
	int		i;

	i = 0;
	while (src[i])
		i++;
	dest = ft_calloc(i + 1, sizeof(char));
	if (!dest)
		return (NULL);
	dest[i] = '\0';
	i--;
	while (i >= 0)
	{
		dest[i] = src[i];
		i--;
	}
	return (dest);
}

// #include <stdio.h>
// int main(void)
// {
// 	char testSrc[] = {'\0'};
// 	char *testDest = ft_strdup(testSrc);

// 	printf("%s", testDest);
// }