/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:06:46 by dabalm            #+#    #+#             */
/*   Updated: 2024/02/27 14:06:06 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_character(t_map *map, int **been, t_vector v)
{
	if (been[(int)v.y][(int)v.x])
	{
		if (map->matrix[(int)v.y][(int)v.x] == ' '
			|| map->matrix[(int)v.y][(int)v.x] == '\0')
			ft_printf("\033[1;31m*\033[0m");
		else
		{
			if (v.y == 0 || !map->matrix[(int)v.y + 1] || v.x == 0
				|| !map->matrix[(int)v.y][(int)v.x + 1])
				ft_printf("\033[1;31m%c\033[0m",
					map->matrix[(int)v.y][(int)v.x]);
			else
				ft_printf("\033[1;36m%c\033[0m",
					map->matrix[(int)v.y][(int)v.x]);
		}
	}
	else
		ft_printf("%c", map->matrix[(int)v.y][(int)v.x]);
}

static void	print_matrix(t_map *map, int **been)
{
	t_vector	v;

	v.y = 0;
	while (v.y < map->size.y)
	{
		v.x = 0;
		while (v.x < map->size.x)
		{
			print_character(map, been, v);
			v.x++;
		}
		ft_printf("\n");
		v.y++;
	}
}

int	**create_been_matrix(t_map *map)
{
	int	**been;
	int	i;

	been = ft_calloc(map->size.y, sizeof(int *));
	if (!been)
	{
		ft_putstr_fd("Error: malloc failed in floodfill.\n", 2);
		return (NULL);
	}
	i = 0;
	while (i < map->size.y)
	{
		been[i] = ft_calloc(map->size.x, sizeof(int));
		i++;
	}
	return (been);
}

/**
 * @details goes through entire map and fills been,
	also exits program when it hits the side of the map
*/
int	floodfill(t_map *map, int **been, int x, int y)
{
	if (map->matrix[y][x] == '1' || been[y][x] == 1)
		return (1);
	been[y][x] = 1;
	ft_putstr_fd("\e[1;1H\e[2J", 1);
	print_matrix(map, been);
	usleep(30000);
	if (x <= 0 || y <= 0 || x >= map->size.x - 1 || y >= map->size.y - 1)
	{
		ft_putstr_fd("Floodfill failed\n", 2);
		free_been_matrix(been, map);
		return (0);
	}
	if (!floodfill(map, been, x + 1, y))
		return (0);
	if (!floodfill(map, been, x - 1, y))
		return (0);
	if (!floodfill(map, been, x, y + 1))
		return (0);
	if (!floodfill(map, been, x, y - 1))
		return (0);
	return (1);
}

int	do_floodfill(t_game *game)
{
	int	**been;

	been = create_been_matrix(&game->map);
	if (!been)
		return (0);
	else if (!floodfill(&game->map, been,
			game->player.position.x, game->player.position.y))
		return (0);
	free_been_matrix(been, &game->map);
	return (1);
}
