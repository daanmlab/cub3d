/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:07:13 by dabalm            #+#    #+#             */
/*   Updated: 2023/10/07 18:45:21 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	new_nb;
	char	nb_as_string[10];
	int		i;

	new_nb = n;
	if (n == 0)
		write(fd, "0", 1);
	if (n < 0)
	{
		write(fd, "-", 1);
		new_nb *= -1;
	}
	i = 0;
	while (new_nb > 0)
	{
		nb_as_string[i] = (new_nb % 10) + '0';
		new_nb /= 10;
		i++;
	}
	i--;
	while (i >= 0)
	{
		write(fd, &nb_as_string[i], 1);
		i--;
	}
}
