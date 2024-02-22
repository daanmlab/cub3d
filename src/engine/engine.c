/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:43:12 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/02/22 13:30:43 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	engine(t_player player, t_map map, t_img *img)
{
	static t_engine	this;

	draw_floor_and_ceiling(map, player, img);
	player.map_square = new_vector(floor(player.position.x),
			floor(player.position.y));
	this.wall_square = new_vector(player.map_square.x, player.map_square.y);
	this.plane_multiplier = 2 / WIDTH;
	this.wall_hit = false;
	this.pixel = 0;
	while (this.pixel < WIDTH)
	{
		this.ray_dir = v_sum(player.direction, 
				v_mult(player.plane, -1 + this.pixel * this.plane_multiplier));
		this.delta_x = fabs(1 / this.ray_dir.x + 0.000001);
		this.delta_y = fabs(1 / this.ray_dir.y + 0.000001);
		set_distances_to_sides(&player, &this);
		dda_find_wall(&this, map.matrix);
		calculate_distances_to_wall(&player, &this);
		setup_texture(&this, map, &player, img);
		draw_wall_line(&this, map, &player, img);
		this.pixel++;
	}
}
