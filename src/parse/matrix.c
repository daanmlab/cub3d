/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:34:10 by dabalm            #+#    #+#             */
/*   Updated: 2024/02/23 21:00:16 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int standardize_matrix(t_map *map)
{
    int i;
    char *temp;

    i = 0;
    while (i < map->size.y)
    {
        temp = map->matrix[i];
        map->matrix[i] = ft_calloc(map->size.x + 1, sizeof(char));
        if (!map->matrix[i])
            return (ft_printf("malloc failed") && 0);
        ft_strlcpy(map->matrix[i], temp, map->size.x);
        free(temp);
        i++;
    }

	
	for (int i = 0; i < map->size.y; i++) 
	{
		for (int j = 0; j < map->size.x; j++) 
			printf("%c", map->matrix[i][j]);
		printf("\n");
	}
	
	// map->real_map = ft_calloc(map->size.y, sizeof(int *));
	// for (int i = 0; i < map->size.y; i++)
	// {
	// 	map->real_map[i] = ft_calloc(map->size.x, sizeof(int));
	// 	for (int j = 0; j < map->size.x; j++)
	// 	{
	// 		if (map->matrix[i][j] == '')
	// 		map->real_map[i][j] = map->matrix[i][j] == '1' ? 1 : 0;
	// 	}
	// }
    return 1;
}

void free_matrix(char **matrix)
{
    int i;

    i = 0;
    while (matrix[i])
        free(matrix[i++]);
    free(matrix);
}

char **realloc_matrix(char **matrix)
{
    int i;
    char **new_matrix;

    i = 0;
    while (matrix && matrix[i])
        i++;
    new_matrix = ft_calloc(i + 2, sizeof(char *));
    while (i >= 0)
    {
        new_matrix[i] = matrix[i];
        i--;
    }
    free(matrix);
    return new_matrix;
}

static void print_matrix(char **matrix, t_vector pos)
{
    t_vector curr;

    curr.y = 0;
    while (matrix[(int)curr.y])
    {
        curr.x = 0;
        while (matrix[(int)curr.y][(int)curr.x])
        {
            if (curr.y == pos.y && curr.x == pos.x)
                ft_printf("\033[1;31m%c\033[0m", matrix[(int)curr.y][(int)curr.x]);
            else
                ft_printf("%c", matrix[(int)curr.y][(int)curr.x]);
            curr.x++;
        }
        ft_printf("\n");
        curr.y++;
    }
}

int set_matrix(int fd, t_map *map)
{
    char *line;
    int i;
    int x;
    
    i = 0;
    x = 0;
    line = get_next_line(fd);
    map->matrix = ft_calloc(2, sizeof(char *));
    while (line)
    {
        map->matrix[i] = ft_strtrim(line, "\n");
        if (map->matrix[i] && ft_strlen(map->matrix[i]) > x)
            x = ft_strlen(map->matrix[i]);
        map->matrix = realloc_matrix(map->matrix);
        free(line);
        line = get_next_line(fd);
        i++;
    }
    map->size.y = i;
    map->size.x = x;
    return !!i;
}

/**
 * @details checks for unknown characters :)
*/
int check_matrix(t_game *game)
{
    t_vector curr;
    char *allowed_chars;

    allowed_chars = "01NSEW ";

    curr.y = 0;
    while (game->map.matrix[(int)curr.y])
    {
        curr.x = 0;
        while (game->map.matrix[(int)curr.y][(int)curr.x])
        {
            if (!ft_strchr(allowed_chars, game->map.matrix[(int)curr.y][(int)curr.x]))
            {
                ft_printf("bad char: '%c'; at %d,%d\n", game->map.matrix[(int)curr.y][(int)curr.x], curr.y, curr.x);
                print_matrix(game->map.matrix, curr);
                return 0;
            }
            curr.x++;
        }
        curr.y++;
    }
    return 1;
}

int get_matrix(int fd, t_game *game)
{
    if (!set_matrix(fd, &game->map))
        return (ft_printf("no map :(") && 0);
    if (!check_matrix(game))
        return (ft_printf("bad chars in map :(") && 0);
    return standardize_matrix(&game->map);
}
