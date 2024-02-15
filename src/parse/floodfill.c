/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:06:46 by dabalm            #+#    #+#             */
/*   Updated: 2024/02/15 20:44:44 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>

void clear_screen()
{
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 10);
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
    struct s_position curr;

    curr.y = 0;
    while (curr.y < map->size.y)
    {
        curr.x = 0;
        while (curr.x < map->size.x)
        {
            if (been[curr.y][curr.x])
            {
                if (map->matrix[curr.y][curr.x] == ' ' || map->matrix[curr.y][curr.x] == '\0')
                    ft_printf("\033[1;31m*\033[0m");
                else
                    if (curr.y == 0 || !map->matrix[curr.y + 1] || curr.x == 0 || !map->matrix[curr.y][curr.x + 1])
                        ft_printf("\033[1;31m%c\033[0m", map->matrix[curr.y][curr.x]);
                    else
                        ft_printf("\033[1;36m%c\033[0m", map->matrix[curr.y][curr.x]);
            }
            else
                ft_printf("%c", map->matrix[curr.y][curr.x]);
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
    if (!been || !floodfill(&game->map, been, game->player.initial_postion.x, game->player.initial_postion.y))
        return 0;
    return 1;
}