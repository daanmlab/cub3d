/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:43:12 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/02/24 14:36:53 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_engine	engine_constructor(void);
static void	apply_changes_on_player(t_player *player);

int	render_next_frame(t_game *game)
{
	t_engine	this;

	this = engine_constructor();
	apply_changes_on_player(&game->player);
	draw_floor_and_ceiling(game, game->map, game->player, &game->frame);
	this.wall_square = new_vector(game->player.map_square.x,
			game->player.map_square.y);
	while (this.pixel < WIDTH)
	{
		this.ray_dir = v_sum(game->player.direction,
				v_mult(game->player.plane, (double)(-1.0 + this.pixel
						* this.plane_multiplier)));
		this.delta_x = fabs(1.0 / this.ray_dir.x + 0.000001);
		this.delta_y = fabs(1.0 / this.ray_dir.y + 0.000001);
		set_distances_to_sides(&game->player, &this);
		dda_find_wall(&this, game->map.real_map);
		calculate_distances_to_wall(&game->player, &this);
		setup_texture(&this, game->textures);
		draw_wall_line(&this, &game->player, &game->frame);
		this.pixel++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->frame.img, 0, 0);
	return (0);
}

static void	apply_changes_on_player(t_player *player)
{
	if (player->is_walking)
		player->position = v_sum(player->position, v_mult(player->direction, 0.01));
	if (player->is_walking_back)
		player->position = v_sum(player->position, v_mult(player->direction, -0.01));
	if (player->is_looking_left)
	{
		player->plane = v_rotate(player->plane, 0.01);
		player->direction = v_rotate(player->direction, 0.01);
	}

}

static t_engine	engine_constructor(void)
{
	t_engine	new;

	new.dda_distance_x = 0;
	new.dda_distance_y = 0;
	new.delta_x = 0;
	new.delta_y = 0;
	new.dist_to_side_x = 0;
	new.dist_to_side_y = 0;
	new.line_height = 0;
	new.perpendicular_distance = 0;
	new.pixel = 0;
	new.plane_multiplier = 2.0 / WIDTH;
	new.player_to_wall_distance = 0;
	new.step_x = 0;
	new.step_y = 0;
	new.text_x = 0;
	new.text_y = 0;
	new.text_y_step = 0;
	new.wall_hit = false;
	new.wall_hit_x = 0;
	return (new);
}
