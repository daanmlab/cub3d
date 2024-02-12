/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:44:16 by dabalm            #+#    #+#             */
/*   Updated: 2023/10/07 18:16:13 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_int_length(int n)
{
	long	nb;
	int		count;

	nb = n;
	count = 0;
	if (nb <= 0)
	{
		count++;
		nb = -nb;
	}
	while (nb > 0)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		len;
	char	*result;

	len = get_int_length(n);
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	nb = n;
	result[0] = '0';
	if (nb < 0)
	{
		result[0] = '-';
		nb = -nb;
	}
	len--;
	while (nb > 0)
	{
		result[len] = (nb % 10) + '0';
		nb /= 10;
		len--;
	}
	return (result);
}

// #include <stdio.h>
// int main(void)
// {
// 	printf("%s", ft_itoa(-123456789));
// 	printf("%s", ft_itoa(-123456789));
// 	printf("%s", ft_itoa(-123456789));
// 	printf("%s", ft_itoa(-123456789));
// }