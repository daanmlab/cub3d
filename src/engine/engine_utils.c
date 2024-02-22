/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 01:31:28 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/02/22 13:05:50 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_texture(t_engine *this, t_map map, t_player *player, t_img *img)
{
	this->text_y = 0;
	this->text_y_step = TEXTURE_SIZE / this->line_height;
	this->text_x = this->wall_hit_x * TEXTURE_SIZE;
	if ((this->wall_direction == EAST || this->wall_direction == WEST
			&& (this->ray_dir.x < 0)) || 
		(this->wall_direction == NORTH || this->wall_direction == SOUTH
			&& (this->ray_dir.y > 0)))
		this->text_x = TEXTURE_SIZE - this->text_x - 1;
	if (this->wall_direction == EAST)
			this->selected_texture = map.east_texture;
		else if (this->wall_direction == WEST)
			this->selected_texture = map.west_texture;
		else if (this->wall_direction == NORTH)
			this->selected_texture = map.north_texture;
		else
			this->selected_texture = map.south_texture;
}

void	draw_wall_line(t_engine *this, t_map map, t_player *player, t_img *img)
{
	t_vector		tmp;
	char			*text_pixel;
	unsigned int	color;

	tmp.x = this->pixel;
	tmp.y = (HEIGHT / 2 - this->line_height / 2) * player->pov_rotation_y_axis;
	while (tmp.y < this->line_height * player->pov_rotation_y_axis)
	{
		text_pixel = this->selected_texture.addr
			+ ((int)this->text_y * this->selected_texture.line_length
			+ (int)this->text_x
			* (this->selected_texture.bits_per_pixel / 8));
		color = (unsigned int)text_pixel;
		if (tmp.y < 0 && tmp.y > HEIGHT)
			break ;
		my_mlx_pixel_put(img, tmp, color);
		this->text_y += this->text_y_step;
		tmp.y++;
	}
}

void	calculate_distances_to_wall(t_player *player, t_engine *this)
{
	if (this->wall_direction == WEST || this->wall_direction == EAST)
		this->player_to_wall_distance = fabs(player->position.x
				- this->wall_square.x
				+ (double)this->step_x == -1)
			/ this->ray_dir.x
			* v_magnitude(this->ray_dir);
	else
		this->player_to_wall_distance = fabs(player->position.y
				- this->wall_square.y
				+ (double)this->step_y == -1)
			/ this->ray_dir.y
			* v_magnitude(this->ray_dir);
	this->perpendicular_distance = this->player_to_wall_distance 
			/ v_magnitude(this->ray_dir);
	this->line_height = (HEIGHT / this->perpendicular_distance);
	if (this->wall_direction == WEST || this->wall_direction == EAST)
		this->wall_hit_x = player->position.y + this->perpendicular_distance
			/ this->ray_dir.y;
	else
		this->wall_hit_x = player->position.x + this->perpendicular_distance
			/ this->ray_dir.x;
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
				this->wall_direction = EAST;
			else
				this->wall_direction = WEST;
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
			/ this->delta_x;
		this->step_x = 1;
	}
	else
	{
		this->dist_to_side_x = (player->position.x - player->map_square.x)
			/ this->delta_x;
		this->step_x = -1;
	}
	if (this->ray_dir.y > 0)
	{
		this->dist_to_side_y = (player->map_square.y - player->position.y + 1)
			/ this->delta_y;
		this->step_y = 1;
	}
	else
	{
		this->dist_to_side_y = (player->position.y - player->map_square.y)
			/ this->delta_y;
		this->step_y = -1;
	}
}

