/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:06:46 by dabalm            #+#    #+#             */
/*   Updated: 2024/02/24 01:09:07 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>

void clear_screen()
{
  char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  ft_putstr_fd(CLEAR_SCREEN_ANSI, 1);
}

void	free_been_matrix(int **been, t_map *map)
{
	int	i;
    
	i = 0;
	while (i < map->size.y)
	{
		free(been[i]);
		i++;
	}
	free(been);
}

static void print_matrix(t_map *map, int **been)
{
    t_vector curr;

    curr.y = 0;
    while (curr.y < map->size.y)
    {
        curr.x = 0;
        while (curr.x < map->size.x)
        {
            if (been[(int)curr.y][(int)curr.x])
            {
                if (map->matrix[(int)curr.y][(int)curr.x] == ' ' || map->matrix[(int)curr.y][(int)curr.x] == '\0')
                    ft_printf("\033[1;31m*\033[0m");
                else
                    if (curr.y == 0 || !map->matrix[(int)curr.y + 1] || curr.x == 0 || !map->matrix[(int)curr.y][(int)curr.x + 1])
                        ft_printf("\033[1;31m%c\033[0m", map->matrix[(int)curr.y][(int)curr.x]);
                    else
                        ft_printf("\033[1;36m%c\033[0m", map->matrix[(int)curr.y][(int)curr.x]);
            }
            else
                ft_printf("%c", map->matrix[(int)curr.y][(int)curr.x]);
            curr.x++;
        }
        ft_printf("\n");
        curr.y++;
    }
}

int	**create_been_matrix(t_map *map)
{
	int	**been;
	int	i;

	been = ft_calloc(map->size.y, sizeof(int *));
	if (!been)
    {
        ft_printf("Error: malloc failed in floodfill.\n");
		return NULL;
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
	if (
        map->matrix[y][x] == '1' || 
        been[y][x] == 1)
		return 1;
	been[y][x] = 1;
    clear_screen();
    print_matrix(map, been);
    usleep(60000);
	if (x <= 0 || y <= 0 || x >= map->size.x - 1 || y >= map->size.y - 1)
	{
		ft_printf("Floodfill failed\n");
		free_been_matrix(been, map);
        return 0;
	}
	if (!floodfill(map, been, x + 1, y))
        return (0);
	if (!floodfill(map, been, x - 1, y))
        return (0);
	if (!floodfill(map, been, x, y + 1))
        return (0);
	if (!floodfill(map, been, x, y - 1))
        return (0);
    return 1;
}

int do_floodfill(t_game *game)
{
    int **been;

    ft_printf("y: %d, x: %d\n", game->map.size.y, game->map.size.x);
    been = create_been_matrix(&game->map);
    if (!been || !floodfill(&game->map, been, game->player.position.x, game->player.position.y))
        return 0;
    return 1;
}
