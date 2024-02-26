/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 01:31:28 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/02/26 12:14:00 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_texture(t_engine *this, t_textures textures, t_player *player)
{
	this->text_y = 0;
	this->text_y_step = TEXTURE_SIZE / this->line_height;
	this->text_x = this->wall_hit_x * TEXTURE_SIZE;
	if (((this->wall_direction == EAST || this->wall_direction == WEST)
			&& this->ray_dir.x > 0
			&& (player-> initial_dir == 'E' || player->initial_dir == 'W'))
		|| ((this->wall_direction == SOUTH || this->wall_direction == NORTH)
			&& this->ray_dir.y < 0
			&& (player->initial_dir == 'E' || player->initial_dir == 'W')))
		this->text_x = TEXTURE_SIZE - this->text_x - 1;
	else if (((this->wall_direction == EAST || this->wall_direction == WEST)
			&& this->ray_dir.x < 0
			&& (player-> initial_dir == 'N' || player->initial_dir == 'S'))
		|| ((this->wall_direction == SOUTH || this->wall_direction == NORTH)
			&& this->ray_dir.y > 0
			&& (player->initial_dir == 'N' || player->initial_dir == 'S')))
		this->text_x = TEXTURE_SIZE - this->text_x - 1;
	if (this->wall_direction == EAST)
		this->selected_texture = textures.east;
	else if (this->wall_direction == WEST)
		this->selected_texture = textures.west;
	else if (this->wall_direction == NORTH)
		this->selected_texture = textures.north;
	else
		this->selected_texture = textures.south;
}

void	draw_wall_line(t_engine *this, t_player *player, t_img *img)
{
	t_vector		tmp;
	char			*text_pixel;
	unsigned int	color;

	this->text_y = 0;
	tmp.x = this->pixel;
	tmp.y = ((HEIGHT / 2.0 * (1 + player->pov_rotation_y_axis))
			- this->line_height / 2.0);
	while (tmp.y < ((HEIGHT / 2.0 * (1 + player->pov_rotation_y_axis))
			+ this->line_height / 2.0))
	{
		text_pixel = this->selected_texture.addr
			+ ((int)this->text_y * this->selected_texture.line_length
				+ (int)this->text_x
				* (this->selected_texture.bits_per_pixel / 8));
		color = *(unsigned int *)text_pixel;
		if (tmp.y > 0 && tmp.y < HEIGHT)
			my_mlx_pixel_put(img, tmp, color);
		this->text_y += this->text_y_step;
		tmp.y++;
	}
}

void	calculate_distances_to_wall(t_player *player, t_engine *this)
{
	if (this->wall_direction == WEST || this->wall_direction == EAST)
		this->player_to_wall_distance = fabs(this->wall_square.x
				- player->position.x
				+ (double)(this->step_x == -1.0))
			/ this->ray_dir.x
			* v_magnitude(this->ray_dir);
	else
		this->player_to_wall_distance = fabs(this->wall_square.y
				- player->position.y
				+ (double)(this->step_y == -1.0))
			/ this->ray_dir.y
			* v_magnitude(this->ray_dir);
	this->perpendicular_distance = fabs(this->player_to_wall_distance)
		/ v_magnitude(this->ray_dir);
	this->line_height = HEIGHT / (this->perpendicular_distance + 0.000001);
	if (this->wall_direction == WEST || this->wall_direction == EAST)
		this->wall_hit_x = (player->position.y + this->perpendicular_distance
				* this->ray_dir.y) - this->wall_square.y;
	else
		this->wall_hit_x = (player->position.x + this->perpendicular_distance
				* this->ray_dir.x) - this->wall_square.x;
	this->wall_hit_x -= floor(this->wall_hit_x);
}

void	dda_find_wall(t_engine *this, int **map)
{
	this->dda_distance_x = this->dist_to_side_x;
	this->dda_distance_y = this->dist_to_side_y;
	while (!this->wall_hit)
	{
		if (this->dda_distance_x < this->dda_distance_y)
		{
			this->dda_distance_x += this->delta_x;
			this->wall_square.x += this->step_x;
			if (this->ray_dir.x > 0)
				this->wall_direction = EAST;
			else
				this->wall_direction = WEST;
		}
		else
		{
			this->dda_distance_y += this->delta_y;
			this->wall_square.y += this->step_y;
			if (this->ray_dir.y > 0)
				this->wall_direction = SOUTH;
			else
				this->wall_direction = NORTH;
		}
		if (map[(int)this->wall_square.y][(int)this->wall_square.x] != 0)
			this->wall_hit = true;
	}
}

void	set_distances_to_sides(t_player *player, t_engine *this)
{
	if (this->ray_dir.x > 0)
	{
		this->dist_to_side_x = (player->map_square.x - player->position.x + 1)
			* this->delta_x;
		this->step_x = 1.0;
	}
	else
	{
		this->dist_to_side_x = (player->position.x - player->map_square.x)
			* this->delta_x;
		this->step_x = -1.0;
	}
	if (this->ray_dir.y > 0)
	{
		this->dist_to_side_y = (player->map_square.y - player->position.y + 1)
			* this->delta_y;
		this->step_y = 1.0;
	}
	else
	{
		this->dist_to_side_y = (player->position.y - player->map_square.y)
			* this->delta_y;
		this->step_y = -1.0;
	}
}
