/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:43:12 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/02/21 18:18:34 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_distances_to_sides(t_player *player, t_engine *this);
static void	calculate_distances_to_wall(t_player *player, t_engine *this);
static void	dda_find_wall(t_engine *this, int **map);
static void	draw_wall_line(t_engine *this, t_map map, int pixel_num,
				t_img *img);

void	engine(t_player player, t_map map, t_img *img)
{
	static t_engine	this;
	int				pixel_num;

	draw_floor_and_ceiling(map, player, img);
	player.map_square = new_vector(floor(player.position.x),
			floor(player.position.y));
	this.wall_square = new_vector(player.map_square.x, player.map_square.y);
	this.plane_multiplier = 2 / WIDTH;
	this.wall_hit = false;
	pixel_num = 0;
	while (pixel_num <= WIDTH)
	{
		this.ray_dir = v_sum(player.direction, 
				v_mult(player.plane, -1 + pixel_num * this.plane_multiplier));
		this.delta_x = fabs(1 / this.ray_dir.x + 0.000001);
		this.delta_y = fabs(1 / this.ray_dir.y + 0.000001);
		set_distances_to_sides(&player, &this);
		dda_find_wall(&this, map.matrix);
		calculate_distances_to_wall(&player, &this);
		draw_wall_line(&this, map, pixel_num, img);
	}
}

static void	draw_wall_line(t_engine *this, t_map map, int pixel_num, t_img *img)
{
	int	y;

	this->text_x = this->wall_hit_x * TEXTURE_SIZE;
	if ((this->wall_direction == EAST || this->wall_direction == WEST
			&& (this->ray_dir.x > 0)) || 
		(this->wall_direction == NORTH || this->wall_direction == SOUTH
			&& (this->ray_dir.y > 0)))
		this->text_x = TEXTURE_SIZE - this->text_x - 1;
	y = HEIGHT / 2 - this->line_height / 2;
	while (y < this->line_height)
	{
		if (this->wall_direction == EAST)
			this->pixel_color = map.east_texture[this->text_y][this->text_x];
		else if (this->wall_direction == WEST)
			this->pixel_color = map.west_texture[this->text_y][this->text_x];
		else if (this->wall_direction == NORTH)
			this->pixel_color = map.north_texture[this->text_y][this->text_x];
		else
			this->pixel_color = map.south_texture[this->text_y][this->text_x];
		if (y > 0 && y < HEIGHT)
			my_mlx_pixel_put(img, new_vector(pixel_num, y), this->pixel_color);
		this->text_y += this->text_y_step;
		y++;
	}
}

static void	calculate_distances_to_wall(t_player *player, t_engine *this)
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
	this->texture_y = 0;
	this->texture_y_step = TEXTURE_SIZE / this->line_height;
	if (this->wall_direction == WEST || this->wall_direction == EAST)
		this->wall_hit_x = player->position.y + this->perpendicular_distance
			/ this->ray_dir.y;
	else
		this->wall_hit_x = player->position.x + this->perpendicular_distance
			/ this->ray_dir.x;
}

static void	dda_find_wall(t_engine *this, int **map)
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

static void	set_distances_to_sides(t_player *player, t_engine *this)
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
