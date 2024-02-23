/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:43:12 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/02/23 23:49:05 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	engine(t_game *game)
{
	t_engine	this;

	draw_floor_and_ceiling(game, game->map, game->player, &game->frame);
	game->player.map_square = new_vector(floor(game->player.position.x),
			floor(game->player.position.y));
	this.wall_square = new_vector(game->player.map_square.x,
			game->player.map_square.y);
	this.plane_multiplier = 2 / WIDTH;
	this.wall_hit = false;
	this.pixel = 0;
	while (this.pixel < WIDTH)
	{
		this.ray_dir = v_sum(game->player.direction, 
				v_mult(game->player.plane, -1 + this.pixel
					* this.plane_multiplier));
		this.delta_x = fabs(1 / this.ray_dir.x + 0.000001);
		this.delta_y = fabs(1 / this.ray_dir.y + 0.000001);
		set_distances_to_sides(&game->player, &this);
		dda_find_wall(&this, game->map.matrix);
		calculate_distances_to_wall(&game->player, &this);
		setup_texture(&this, game->textures, &game->player, &game->frame);
		draw_wall_line(&this, &game->player, &game->frame);
		this.pixel++;
	}
}
