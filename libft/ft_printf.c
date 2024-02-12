/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:45:05 by dabalm            #+#    #+#             */
/*   Updated: 2024/02/12 15:29:03 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	contains(char t, char *o)
{
	while (*o)
	{
		if (t == *o)
			return (1);
		o++;
	}
	return (0);
}

int	put_str(char *str)
{
	char	*temp;

	temp = str;
	if (!temp)
		temp = "(null)";
	ft_putstr_fd((char *)temp, 1);
	return (ft_strlen(temp));
}


int	checktype(char *t, va_list d)
{
	char	*options;

	options = "cspdiuxX%";
	if (!contains(*t, options))
		return (0);
	t++;
	if (*t == 'c')
		ft_putchar_fd(va_arg(d, int), 1);
	else if (*t == 's')
		return (put_str(va_arg(d, char *)));
	else if (*t == 'd' || *t == 'i')
		return (putnbr_base(va_arg(d, int), "0123456789"));
	else if (*t == 'p')
		return (put_pointer_addr(va_arg(d, void *)));
	else if (*t == 'u')
		return (putnbr_base(va_arg(d, unsigned int), "0123456789"));
	else if (*t == 'x')
		return (putnbr_base(va_arg(d, unsigned int), "0123456789abcdef"));
	else if (*t == 'X')
		return (putnbr_base(va_arg(d, unsigned int), "0123456789ABCDEF"));
	else if (*t == '%')
		ft_putchar_fd('%', 1);
	return (1);
}

int	ft_printf(const char *format, ...)
{
	char	*f;
	int		i;
	va_list	data;

	if (!format)
		return (-1);
	va_start(data, format);
	f = (char *)format;
	i = 0;
	while (*f)
	{
		if (*f == '%')
		{
			i += checktype(f, data);
			f += 2;
		}
		else
		{
			ft_putchar_fd(*f, 1);
			f++;
			i++;
		}
	}
	va_end(data);
	return (i);
}

// #include <stdio.h>
// int main(void)
// {
// 	// int testnum = NULL;
// 	// char *teststr = NULL;
// 	// ft_printf("%c, %s, %p, %d, %i, %u, %x, %X, %%\n", testnum, teststr,
// &testnum, testnum, testnum, testnum, testnum, testnum);
// 	// printf("%c, %s, %p, %d, %i, %u, %x, %X, %%\n\n", testnum, teststr,
// &testnum, testnum, testnum, testnum, testnum, testnum);

// 	// ft_printf(" %c %c %c \n", 0, '1', '2');
// 	// printf(" %c %c %c \n\n", 0, '1', '2');

// 	printf("m:%d \n",
// 		ft_printf("%p", (void *)-2)
// 	);
// 	printf("t:%d ",
// 		printf("%p ", (void *)-2)
// 	);

// 	// printf("%ld, %ld", LONG_MIN, LONG_MAX);
// }
