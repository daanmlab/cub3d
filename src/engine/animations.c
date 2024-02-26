/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 18:09:39 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/02/26 12:12:40 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_hud_object_algo(t_vector origin, t_game *game, t_img *obj);

void	running_animation(t_player *player)
{
	if (player->is_running == 2 && v_magnitude(player->plane) < 0.68)
		player->plane = v_mult(player->plane, 1.0009);
	else if (player->is_running != 2 && v_magnitude(player->plane) > 0.66)
		player->plane = v_mult(player->plane, 0.9991);
}

void	draw_hud_object(t_game *game, t_player *player)
{
	if (player->weapon_type == PRIMARY)
		draw_hud_object_algo((t_vector){player->primary_weapon_origin.x,
			player->primary_weapon_origin.y + player->animation_curve},
			game, &player->primary_weapon);
	else if (player->weapon_type == SECONDARY)
		draw_hud_object_algo((t_vector){player->secondary_weapon_origin.x,
			player->secondary_weapon_origin.y + player->animation_curve},
			game, &player->secondary_weapon);
}

static void	draw_hud_object_algo(t_vector origin, t_game *game, t_img *obj)
{
	t_pixel	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < HEIGHT / 2.5)
	{
		j = 0;
		while (j < WIDTH / 2.5)
		{
			tmp.text_x = j * 256 / (WIDTH / 2.5);
			tmp.text_y = i * 256 / (HEIGHT / 2.5);
			tmp.x = origin.x + j;
			tmp.y = origin.y + i;
			tmp.adr = obj->addr + ((int)tmp.text_y * obj->line_length
					+ (int)tmp.text_x * (obj->bits_per_pixel / 8));
			tmp.color = *(unsigned int *)tmp.adr;
			if (tmp.color < 0xFFFFFF && tmp.x < WIDTH && tmp.y < HEIGHT)
				my_mlx_pixel_put(&game->frame, (t_vector){tmp.x, tmp.y},
					tmp.color);
			j++;
		}
		i++;
	}
}

void	setup_animation_curve(t_player *player)
{
	static int	signal;

	if (signal == 0)
		player->animation_curve += 0.10
			* (1.0 + (player->is_walking * 1.5) + player->is_running * 3);
	else
		player->animation_curve -= 0.10
			* (1.0 + (player->is_walking * 1.5) + player->is_running * 3);
	if (player->animation_curve > 15)
		signal = 1;
	else if (player->animation_curve <= 0)
		signal = 0;
}

void	changing_weapon_animation(t_player *player)
{
	if (player->weapon_type == PRIMARY
		&& player->secondary_weapon_origin.y < HEIGHT)
		player->secondary_weapon_origin.y += 10.0;
	else if (player->weapon_type == SECONDARY
		&& player->primary_weapon_origin.y < HEIGHT)
		player->primary_weapon_origin.y += 10.0;
	else if (player->weapon_type == PRIMARY
		&& player->primary_weapon_origin.y > HEIGHT - (WIDTH / 3.0) + 120.0)
		player->primary_weapon_origin.y -= 10.0;
	else if (player->weapon_type == SECONDARY
		&& player->secondary_weapon_origin.y > HEIGHT - (WIDTH / 3.0) + 120.0)
		player->secondary_weapon_origin.y -= 10.0;
}
