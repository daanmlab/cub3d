/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:43:12 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/02/25 17:29:58 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_ray(t_engine *this, t_player player);
static void	apply_changes_on_player(t_player *player, int **map);

int	render_next_frame(t_game *game)
{
	t_engine	this;

	apply_changes_on_player(&game->player, game->map.real_map);
	draw_floor_and_ceiling(game, game->map, game->player, &game->frame);
	this.wall_square = new_vector(game->player.map_square.x,
			game->player.map_square.y);
	if (player->is_running)
	this.pixel = 0;
	while (this.pixel < WIDTH)
	{
		setup_ray(&this, game->player);
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

static bool	no_colision(t_player *player, char side, int **map)
{
	t_vector tmp;

	if (side == 'f')
		tmp = v_sum(player->position, v_mult(player->dir, 0.2));
	else if (side == 'b')
		tmp = v_sum(player->position, v_mult(player->dir, -0.2));
	else if (side == '1')
		tmp = v_sum (player->position, v_mult(v_rotate(player->dir, PI / 2), -0.2));
	else
		tmp = v_sum (player->position, v_mult(v_rotate(player->dir, PI / 2), 0.2));
	return (map[(int)floorf(tmp.y)][(int)floorf(tmp.x)] == 0);
}

static t_vector	walk(t_player *player, char side, int **map)
{
	if (side == 'f' && no_colision(player, side, map))
		return (v_sum(player->position, v_mult(player->dir, 0.01)));
	else if (side == 'b' && no_colision(player, side, map))
		return (v_sum(player->position, v_mult(player->dir, -0.01)));
	else if ((((player->initial_dir == 'N' || player->initial_dir == 'S') && side == 'l')
		|| ((player->initial_dir == 'E' || player->initial_dir == 'W') && side == 'r'))
		&& no_colision(player, '1', map))
		return (v_sum (player->position, v_mult(v_rotate(player->dir, PI / 2), -0.01)));
	else if ((((player->initial_dir == 'N' || player->initial_dir == 'S') && side == 'r')
		|| ((player->initial_dir == 'E' || player->initial_dir == 'W') && side == 'l'))
		&& no_colision(player, '2', map))
		return (v_sum (player->position, v_mult(v_rotate(player->dir, PI / 2), 0.01)));
	else
		return(player->position);
}

static void	apply_changes_on_player(t_player *player, int **map)
{
	if (player->is_walking)
		player->position = walk(player, 'f', map);
	else if (player->is_walking_back)
		player->position = walk(player, 'b', map);
	else if (player->is_walking_left)
		player->position = walk(player, 'l', map);
	else if (player->is_walking_right)
		player->position = walk(player, 'r', map);
	else if (player->is_running)
		player->pos
	if (player->is_looking_left)
	{
		return ;
	}
	player->map_square = new_vector(floor(player->position.x),
			floor(player->position.y));
}

static void	setup_ray(t_engine *this, t_player player)
{
	this->dda_distance_x = 0;
	this->dda_distance_y = 0;
	this->dist_to_side_x = 0;
	this->dist_to_side_y = 0;
	this->line_height = 0;
	this->perpendicular_distance = 0;
	this->plane_multiplier = 2.0 / WIDTH;
	this->player_to_wall_distance = 0;
	this->step_x = 0;
	this->step_y = 0;
	this->text_x = 0;
	this->text_y = 0;
	this->text_y_step = 0;
	this->wall_hit = false;
	this->wall_hit_x = 0;
	this->wall_square = new_vector(player.map_square.x, player.map_square.y);
	this->ray_dir = v_sum(player.dir,
			v_mult(player.plane, -1.0 + this->pixel * this->plane_multiplier));
	this->delta_x = fabs(1.0 / (this->ray_dir.x + 0.000001));
	this->delta_y = fabs(1.0 / (this->ray_dir.y + 0.000001));
}
