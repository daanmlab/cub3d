/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:56:43 by dabalm            #+#    #+#             */
/*   Updated: 2023/11/16 17:00:31 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	clean_buffer(char *buffer)
{
	int	i;

	i = 0;
	while (buffer && i < BUFFER_SIZE)
	{
		buffer[i] = 0;
		i++;
	}
}

void	buffer_fix(char *nl_pointer, char *buffer)
{
	if (nl_pointer[1] == '\0')
		clean_buffer(buffer);
	else
		gnl_strcpy(buffer, nl_pointer + 1);
}

char	*get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*result;
	char		*nl_pointer;

	if (read(fd, 0, 0) < 0 || BUFFER_SIZE < 1 || fd >= FOPEN_MAX)
	{
		if (fd > 0 && fd < FOPEN_MAX && read(fd, 0, 0) >= 0)
			clean_buffer(buffer[fd]);
		return (NULL);
	}
	result = NULL;
	while (buffer[fd][0] || read(fd, buffer[fd], BUFFER_SIZE))
	{
		nl_pointer = gnl_strchr(buffer[fd], '\n');
		result = gnl_strjoin(result, buffer[fd]);
		if (nl_pointer)
		{
			buffer_fix(nl_pointer, buffer[fd]);
			break ;
		}
		else
			clean_buffer(buffer[fd]);
	}
	return (result);
}

// #include <fcntl.h>
// int main(void)
// {
//     int fd;
//     char *result;

//     fd = open("multiple_line_w_nl.txt", O_RDONLY);
//     result = get_next_line(fd);
//     printf("final: %s\n", result);
//     free(result);
//     result = get_next_line(fd);
//     printf("final: %s\n", result);
//     free(result);
//     result = get_next_line(fd);
//     printf("final: %s\n", result);
//     free(result);
//     result = get_next_line(fd);
//     printf("final: %s\n", result);
//     free(result);
//     result = get_next_line(fd);
//     printf("final: %s\n", result);
//     free(result);
//     result = get_next_line(fd);
//     printf("final: %s\n", result);
//     free(result);
//     return (0);
// }
