/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 20:58:16 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/02/26 21:30:41 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

char	**realloc_matrix(char **matrix)
{
	int		i;
	char	**new_matrix;

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
	return (new_matrix);
}
