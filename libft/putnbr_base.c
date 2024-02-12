/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 15:27:23 by dabalm            #+#    #+#             */
/*   Updated: 2023/11/16 16:51:38 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_int_len(long n, char *base)
{
	int	baselen;
	int	len;

	baselen = 0;
	while (base[baselen])
		baselen++;
	len = 0;
	while (n != 0)
	{
		n /= baselen;
		len++;
	}
	return (len);
}

static long long	num_check(long n)
{
	long long	nb;

	nb = n;
	if (nb == 0)
	{
		write(1, &"0", 1);
		return (0);
	}
	if (nb < 0)
	{
		write(1, &"-", 1);
		return (-nb);
	}
	return (nb);
}

int	putnbr_base(long n, char *base)
{
	char		*str;
	long long	nb;
	int			num_len;
	int			base_len;
	int			i;

	nb = num_check(n);
	if (!nb)
		return (1);
	base_len = 0;
	while (base[base_len])
		base_len++;
	num_len = get_int_len(nb, base);
	str = ft_calloc(num_len, sizeof(char));
	i = 1;
	while (nb != 0)
	{
		str[num_len - i] = base[nb % base_len];
		nb /= base_len;
		i++;
	}
	write(1, str, num_len);
	free(str);
	return (num_len + (n < 0));
}
