/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:29:53 by dabalm            #+#    #+#             */
/*   Updated: 2024/02/27 12:12:20 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_texture(const char *line, t_map *map)
{
	char	**split;
	int		i;

	split = ft_split(line, ' ');
	i = 0;
	while (split && split[i])
		i++;
	if (i != 2)
		return (!!ft_free_tab(split));
	if (!ft_strncmp(split[0], "NO", 3) && !map->north_texture)
		map->north_texture = ft_strtrim(split[1], "\n ");
	else if (!ft_strncmp(split[0], "SO", 3) && !map->south_texture)
		map->south_texture = ft_strtrim(split[1], "\n ");
	else if (!ft_strncmp(split[0], "WE", 3) && !map->west_texture)
		map->west_texture = ft_strtrim(split[1], "\n ");
	else if (!ft_strncmp(split[0], "EA", 3) && !map->east_texture)
		map->east_texture = ft_strtrim(split[1], "\n ");
	else
		return (!!ft_free_tab(split));
	ft_free_tab(split);
	return (1);
}

int	create_img(t_game *game, t_img *img, char *img_file)
{
	if (open(img_file, O_RDONLY) == -1)
	{
		ft_putstr_fd("file ", 2);
		ft_putstr_fd(img_file, 2);
		ft_putstr_fd(" doesn't exist\n", 2);
		return (0);
	}
	img->x = 0;
	img->y = 0;
	img->img = mlx_xpm_file_to_image(game->mlx, img_file, &img->x, &img->y);
	if (!img->img)
	{
		ft_putstr_fd("invalid file ", 2);
		ft_putstr_fd(img_file, 2);
		return (0);
	}
	img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel),
			&(img->line_length), &(img->endian));
	if (!img->addr)
	{
		mlx_destroy_image(game->mlx, img->img);
		img->img = NULL;
		return (0);
	}
	return (1);
}

int	check_enough_textures(t_game *game)
{
	int		i;
	char	*textures[4];

	textures[0] = game->map.north_texture;
	textures[1] = game->map.south_texture;
	textures[2] = game->map.west_texture;
	textures[3] = game->map.east_texture;
	i = 0;
	while (i < 4 && textures[i])
		i++;
	return (i == 4);
}

int	create_textures(t_game *game)
{
	t_img	*images[4];
	char	*textures[4];
	int		i;

	textures[0] = game->map.north_texture;
	textures[1] = game->map.south_texture;
	textures[2] = game->map.west_texture;
	textures[3] = game->map.east_texture;
	images[0] = &game->textures.north;
	images[1] = &game->textures.south;
	images[2] = &game->textures.west;
	images[3] = &game->textures.east;
	if (!check_enough_textures(game))
		return (ft_putstr_fd("not enough textures\n", 2), 0);
	i = 0;
	while (i < 4 && create_img(game, images[i], textures[i]))
		i++;
	if (i != 4)
		return (0);
	return (1);
}

int	get_textures(int fd, t_game *game)
{
	char	*line;

	line = get_next_line(fd);
	game->map.north_texture = NULL;
	game->map.south_texture = NULL;
	game->map.west_texture = NULL;
	game->map.east_texture = NULL;
	game->textures.north.img = NULL;
	game->textures.south.img = NULL;
	game->textures.west.img = NULL;
	game->textures.east.img = NULL;
	while (!check_enough_textures(game) && line)
	{
		set_texture(line, &game->map);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (create_textures(game));
}
