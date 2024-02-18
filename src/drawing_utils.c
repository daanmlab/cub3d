/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 23:10:27 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/02/18 23:25:09 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	line(t_img *img, t_vector start, t_vector end, int color)
{
	double	difX;
	double	difY;
	int		steps;
	double	incX;
	double	incY;

	difX = end.x - start.x;
	difY = end.y - start.y;
	if (fabs(difX) > fabs(difY))
		steps = (int)round(fabs(difX));
	else
		steps = (int)round(fabs(difY));
	incX = difX / steps;
	incY = difY / steps;
	for (int i = 0; i < steps; i++)
	{
		t_vector pixel = v_sum(start, new_vector(i * incX, i * incY));
		if (pixel.x > 0 && pixel.x < WIDTH && pixel.y > 0 && pixel.y < HEIGHT)
			my_mlx_pixel_put(img, v_sum(start, new_vector(i * incX, i * incY)), color);
	}
}
