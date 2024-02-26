/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 18:09:39 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/02/26 01:09:39 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	running_animation(t_player *player)
{
	if (player->is_running == 2 && v_magnitude(player->plane) < 0.68)
		player->plane = v_mult(player->plane, 1.0009);
	else if (player->is_running != 2 && v_magnitude(player->plane) > 0.66)
		player->plane = v_mult(player->plane, 0.9991);
}

//void	draw_weapon(t_player *player)
//{
	
//}

void	draw_hud_object(t_vector origin, t_game *game, char *filename)
{
	t_img			obj;
	t_pixel			tmp;
	int			i;
	int			j;
	double		text_y;
	double		text_x;
	double		text_x_incrementor;
	double		text_y_incrementor;

	obj.img = mlx_xpm_file_to_image(game->mlx, filename, &obj.width, &obj.height);
	obj.addr = mlx_get_data_addr(obj.img, &obj.bits_per_pixel, &obj.line_length, &obj.endian);

	text_x_incrementor = (double)obj.width / (WIDTH / 5.0);
	text_y_incrementor = (double)obj.width / (HEIGHT / 5.0);
	i = 0;
	while (i < HEIGHT / 5.0)
	{
		j = 0;
		while (j < WIDTH / 5.0)
		{
			text_x = j * text_x_incrementor;
			text_y = i * text_y_incrementor;
			tmp.x = origin.x + j;
			tmp.y = origin.y + i;
			tmp.adr = obj.addr + ((int)text_y * obj.line_length
				+ (int)text_x * (obj.bits_per_pixel / 8));
			tmp.color = *(unsigned int *)tmp.adr;
			if (tmp.color < 0xFFFFFF && tmp.x < WIDTH && tmp.y < HEIGHT)
				my_mlx_pixel_put(&game->frame, (t_vector){tmp.x, tmp.y}, tmp.color);
			j++;
		}
		i++;
	}
}

void	setup_animation_curve(t_player *player)
{
	static int	signal;

	if (signal == 0)
		player->animation_curve += 0.10 * (1.0 + (player->is_walking * 1.5) + player->is_running * 3);
	else
		player->animation_curve -= 0.10 * (1.0 + (player->is_walking * 1.5) + player->is_running * 3);
	if (player->animation_curve > 15)
		signal = 1;
	else if (player->animation_curve <= 0)
		signal = 0;
}
