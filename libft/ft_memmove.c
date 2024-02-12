/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:31:44 by dabalm            #+#    #+#             */
/*   Updated: 2023/10/03 20:28:25 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int			i;
	char		*d;
	const char	*s;

	i = n - 1;
	d = dest;
	s = src;
	if (d > s)
	{
		while (i >= 0)
		{
			d[i] = s[i];
			i--;
		}
	}
	else
	{
		ft_memcpy(d, s, n);
	}
	return (d);
}

// #include <stdio.h>
// int main(void)
// {
//     char test[] = "1234567890";
//     char *dest = test + 4;
//     ft_memmove(dest, test, 5);
//     printf("%s", test);
//     return (0);
// }