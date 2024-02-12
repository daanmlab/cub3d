/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:49:27 by dabalm            #+#    #+#             */
/*   Updated: 2023/11/16 19:44:08 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @returns pointer to char or NULL if not found
*/
char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str)
	{
		if ((unsigned char)*str == (unsigned char)c)
			return (str);
		str++;
	}
	if ((unsigned char)*str == (unsigned char)c)
		return (str);
	return (NULL);
}

// #include <stdio.h>
// int main(void)
// {
//     char *test = "abcdefg";
//     printf("%s",strchr(test, 'd'));
// }