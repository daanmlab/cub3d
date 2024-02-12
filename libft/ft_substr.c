/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:19:04 by dabalm            #+#    #+#             */
/*   Updated: 2023/10/04 18:25:43 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned long	slen;
	char			*result;

	slen = (unsigned long)ft_strlen((char *)s);
	i = start;
	if (start >= slen)
		return (ft_calloc(1, sizeof(char)));
	if (start + len > slen + 1)
		result = ft_calloc((slen - start) + 1, sizeof(char));
	else
		result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	while (s[i] && i < start + len)
	{
		result[i - start] = s[i];
		i++;
	}
	result[i - start] = '\0';
	return (result);
}

// #include <stdio.h>
// int main(void)
// {
//     char *test = "hallo daar";
//     char *result = ft_substr(test, 6, 4);
//     printf("%s\n", result);
// }