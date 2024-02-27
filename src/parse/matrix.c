/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:34:10 by dabalm            #+#    #+#             */
/*   Updated: 2024/02/27 13:34:21 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_real_map(t_map *map)
{
	int	i;
	int	j;

	map->real_map = ft_calloc(map->size.y, sizeof(int *));
	if (!map->real_map)
		return (ft_putstr_fd("error allocating memory\n", 2), -1);
	i = -1;
	while (++i < map->size.y)
	{
		map->real_map[i] = ft_calloc(map->size.x, sizeof(int));
		if (!map->real_map[i])
			return (ft_putstr_fd("error allocating memory\n", 2), -1);
		j = 0;
		while (j < map->size.x)
		{
			if (map->matrix[i][j] == '1')
				map->real_map[i][j] = 1;
			else if (map->matrix[i][j] == '0' || ft_isalpha(map->matrix[i][j]))
				map->real_map[i][j] = 0;
			else
				map->real_map[i][j] = 9;
			j++;
		}
	}
	return (1);
}

int	standardize_matrix(t_map *map)
{
	int		i;
	char	*temp;

	i = 0;
	while (i < map->size.y)
	{
		temp = map->matrix[i];
		map->matrix[i] = ft_calloc(map->size.x + 1, sizeof(char));
		if (!map->matrix[i])
			return (ft_putstr_fd("error allocating memory\n", 2), 0);
		ft_strlcpy(map->matrix[i], temp, map->size.x + 1);
		free(temp);
		i++;
	}
	if (get_real_map(map) == -1)
		return (0);
	return (1);
}

int	set_matrix(int fd, t_map *map)
{
	char	*line;
	int		i;
	int		x;

	i = 0;
	x = 0;
	map->matrix = ft_calloc(2, sizeof(char *));
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map->matrix[i] = ft_strtrim(line, "\n");
		if (ft_strlen(map->matrix[i]) > x)
			x = ft_strlen(map->matrix[i]);
		map->matrix = realloc_matrix(map->matrix);
		free(line);
		i++;
	}
	map->size.y = i;
	map->size.x = x;
	return (!!i);
}

/**
 * @details checks for unknown characters :)
*/
int	check_matrix(t_game *game)
{
	t_vector	curr;
	char		*allowed_chars;

	allowed_chars = "01NSEW ";
	curr.y = 0;
	while (game->map.matrix[(int)curr.y])
	{
		curr.x = 0;
		while (game->map.matrix[(int)curr.y][(int)curr.x])
		{
			if (!ft_strchr(allowed_chars,
					game->map.matrix[(int)curr.y][(int)curr.x]))
				return (0);
			curr.x++;
		}
		curr.y++;
	}
	return (1);
}

int	get_matrix(int fd, t_game *game)
{
	if (!set_matrix(fd, &game->map))
	{
		ft_putstr_fd("no map :(\n", 2);
		return (0);
	}
	if (!check_matrix(game))
	{
		ft_putstr_fd("bad chars in map :(\n", 2);
		return (0);
	}
	return (standardize_matrix(&game->map));
}
