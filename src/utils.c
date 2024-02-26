/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:57:03 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/02/26 12:21:56 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_mouse_x(t_game *game)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(game->mlx, game->mlx_win, &x, &y);
	return (x);
}

int	get_mouse_y(t_game *game)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(game->mlx, game->mlx_win, &x, &y);
	return (y);
}

void	ft_free_int_matrix(int **matrix, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

t_img	img_constructor(t_game *game, char *filename)
{
	t_img	img;

	img.img = mlx_xpm_file_to_image(game->mlx, filename,
			&img.width, &img.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	return (img);
}
