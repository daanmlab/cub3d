/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:46:23 by dabalm            #+#    #+#             */
/*   Updated: 2024/02/13 21:01:56 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file_name(const char *filename)
{
	char		**split;
	static int	result;
	static int	i;

	split = ft_split(filename, '.');
	while (split[i])
		i++;
	i--;
	result = !ft_strncmp(split[i], "cub", ft_strlen(split[i]));
	while (i >= 0)
		free(split[i--]);
	free(split);
	return (result);
}

int	check_args(int argc, char const *argv[])
{
	if (argc < 2)
		return (ft_printf("not enough arguments\n") && 0);
	if (argc > 2)
		return (ft_printf("too many arguments\n") && 0);
	if (!check_file_name(argv[1]))
		return (ft_printf("invalid file name\n") && 0);
	return (1);
}

int	parse(int argc, char const *argv[], t_game *game)
{
	int	fd;

	if (!check_args(argc, argv))
		return (0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (ft_printf("file doesn't exist\n") && 0);
	if (!get_textures(fd, game))
		return 0;
	if (!get_colors(fd, game))
		return !!free_textures(game);
	return (1);
}
