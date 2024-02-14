/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:34:10 by dabalm            #+#    #+#             */
/*   Updated: 2024/02/14 19:54:54 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void print_matrix(char **matrix)
{
    int i;

    i = 0;
    while (matrix[i])
        ft_printf("%s", matrix[i++]);
}

int set_matrix(int fd, t_map *map)
{
    char *line;
    int i;
    
    i = 0;
    line = get_next_line(fd);
    map->matrix = ft_calloc(2, sizeof(char *));
    while (line)
    {
        map->matrix[i++] = line;
        map->matrix = realloc_matrix(map->matrix);
        line = get_next_line(fd);
    }
    return !!i;
}

int get_matrix(int fd, t_game *game)
{
    if (!set_matrix(fd, &game->map))
        return (ft_printf("no map :(") && 0);
    return 1;
}