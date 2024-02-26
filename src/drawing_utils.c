/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 23:10:27 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/02/26 12:22:39 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, t_vector vector, unsigned int color)
{
	char	*dest;

	if (vector.x < 0 || vector.x > WIDTH || vector.y < 0 || vector.y > HEIGHT)
		return ;
	dest = img -> addr + ((int)round(vector.y) * img -> line_length
			+ (int)round(vector.x) * (img -> bits_per_pixel / 8));
	*(unsigned int *)dest = color;
}

void	line(t_img *img, t_vector start, t_vector end, int color)
{
	double	delta_x;
	double	delta_y;
	int		steps;
	int		i;

	delta_x = end.x - start.x;
	delta_y = end.y - start.y;
	if (fabs(delta_x) > fabs(delta_y))
		steps = (int)round(fabs(delta_x));
	else
		steps = (int)round(fabs(delta_y));
	delta_x = delta_x / steps;
	delta_y = delta_y / steps;
	i = 0;
	while (i < steps)
	{
		start.x += delta_x;
		start.y += delta_y;
		if (start.x < 0 || start.x > WIDTH || start.y < 0 || start.y > HEIGHT)
			break ;
		my_mlx_pixel_put(img, start, color);
		i++;
	}
}

void	rectangle(t_img *img, t_rectangle rectangle)
{
	t_vector	tmp;
	int			i;
	int			j;

	tmp = new_vector(rectangle.start.x, rectangle.start.y);
	i = 0;
	while (i < (int)rectangle.height)
	{
		j = 0;
		while (j < (int)rectangle.width)
		{
			tmp.x = rectangle.start.x + j;
			tmp.y = rectangle.start.y + i;
			if (tmp.x < WIDTH && tmp.y < HEIGHT)
				my_mlx_pixel_put(img, tmp, rectangle.color);
			else if (tmp.x > WIDTH && tmp.y > HEIGHT)
				break ;
			j++;
		}
		i++;
	}
}

t_rectangle	new_rectangle(unsigned int width, unsigned int height,
		unsigned int color)
{
	t_rectangle	new;

	new.width = width;
	new.height = height;
	new.color = color;
	return (new);
}

void	draw_floor_and_ceiling(t_game *game, t_map map, t_player player,
			t_img *img)
{
	map.ceiling.start = new_vector(0, 0);
	map.ceiling.height = HEIGHT;
	map.ceiling.width = WIDTH;
	map.ceiling.color = game->ceiling_color.color;
	map.floor.start = new_vector(0, HEIGHT / 2
			* (1 + player.pov_rotation_y_axis));
	map.floor.height = HEIGHT * 5;
	map.floor.width = WIDTH;
	map.floor.color = game->floor_color.color;
	rectangle(img, map.ceiling);
	rectangle(img, map.floor);
}
