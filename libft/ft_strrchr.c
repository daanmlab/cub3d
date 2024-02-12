/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:00:33 by dabalm            #+#    #+#             */
/*   Updated: 2023/10/04 18:35:26 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	*l;

	l = NULL;
	str = (char *)s;
	while (*str)
	{
		if ((unsigned char)*str == (unsigned char)c)
			l = str;
		str++;
	}
	if ((unsigned char)*str == (unsigned char)c)
		l = str;
	return (l);
}
