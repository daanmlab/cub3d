/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:31:28 by dabalm            #+#    #+#             */
/*   Updated: 2023/12/19 23:26:23 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*dest;

	i = 0;
	dest = s;
	while (i < n)
	{
		dest[i] = 0;
		i++;
	}
}

// #include <stdio.h>
// int main(void)
// {
// 	char test[] = "abcdefghijk";
// 	char test1[] = "abcdefghijk";
// 	int i = 0;
// 	ft_bzero(test, 12);
// 	while (i < 12)
// 	{
// 		printf("%d, ", test[i]);
// 		i++;
// 	}

// }