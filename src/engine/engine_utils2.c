/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 18:08:09 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/02/27 12:20:00 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	no_colision(t_player *player, char side, int **map)
{
	t_vector	tmp;

	if (side == 'f')
		tmp = v_sum(player->position, v_mult(player->dir, 0.2));
	else if (side == 'b')
		tmp = v_sum(player->position, v_mult(player->dir, -0.2));
	else if (side == '1')
		tmp = v_sum (player->position, v_mult(v_rotate(player->dir, PI / 2),
					-0.2));
	else
		tmp = v_sum (player->position, v_mult(v_rotate(player->dir, PI / 2),
					0.2));
	return (map[(int)floorf(tmp.y)][(int)floorf(tmp.x)] == 0);
}

t_vector	walk(t_player *player, char side, int **map)
{
	if (side == 'f' && no_colision(player, side, map))
		return (v_sum(player->position, v_mult(player->dir, 0.02)));
	else if (side == 'b' && no_colision(player, side, map))
		return (v_sum(player->position, v_mult(player->dir, -0.02)));
	else if ((((player->initial_dir == 'N' || player->initial_dir == 'S')
				&& side == 'l')
			|| ((player->initial_dir == 'E' || player->initial_dir == 'W')
				&& side == 'r'))
		&& no_colision(player, '1', map))
		return (v_sum (player->position, v_mult(v_rotate(player->dir, PI / 2),
					-0.02)));
	else if ((((player->initial_dir == 'N' || player->initial_dir == 'S')
				&& side == 'r')
			|| ((player->initial_dir == 'E' || player->initial_dir == 'W')
				&& side == 'l'))
		&& no_colision(player, '2', map))
		return (v_sum (player->position, v_mult(v_rotate(player->dir, PI / 2),
					0.02)));
	else if (side == 's' && no_colision(player, 'f', map))
		return (v_sum(player->position, v_mult(player->dir, 0.04)));
	else
		return (player->position);
}

void	apply_changes_on_player(t_game *game, t_player *player, int **map)
{
	if (player->is_running == 2)
		player->position = walk(player, 's', map);
	else if (player->is_walking)
		player->position = walk(player, 'f', map);
	else if (player->is_walking_back)
		player->position = walk(player, 'b', map);
	else if (player->is_walking_left)
		player->position = walk(player, 'l', map);
	else if (player->is_walking_right)
		player->position = walk(player, 'r', map);
	player->delta_mouse_x = get_mouse_x(game) - player->last_mouse_x;
	player->last_mouse_x = get_mouse_x(game);
	if (player->initial_dir == 'N' || player->initial_dir == 'S')
		dir_and_plane_rotate(&player->dir, &player->plane,
			player->delta_mouse_x * player->mouse_sensibility);
	else
		dir_and_plane_rotate(&player->dir, &player->plane,
			-(player->delta_mouse_x * player->mouse_sensibility));
	player->delta_mouse_y = get_mouse_y(game) - player->last_mouse_y;
	player->last_mouse_y = get_mouse_y(game);
	player->pov_rotation_y_axis
		-= player->delta_mouse_y * player->mouse_sensibility;
	player->map_square = new_vector(floor(player->position.x),
			floor(player->position.y));
}

void	setup_ray(t_engine *this, t_player player)
{
	this->plane_multiplier = 2.0 / WIDTH;
	this->text_x = 0;
	this->text_y = 0;
	this->wall_hit = false;
	this->wall_hit_x = 0;
	this->wall_square = new_vector(player.map_square.x, player.map_square.y);
	this->ray_dir = v_sum(player.dir,
			v_mult(player.plane, -1.0 + this->pixel * this->plane_multiplier));
	this->delta_x = fabs(1.0 / (this->ray_dir.x + 0.000001));
	this->delta_y = fabs(1.0 / (this->ray_dir.y + 0.000001));
}

void	dir_and_plane_rotate(t_vector *dir, t_vector *plane, double angle)
{
	*dir = v_rotate(*dir, angle);
	*plane = v_rotate(*plane, angle);
}
