/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:43:12 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/02/27 14:56:44 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_map(int **map, t_vector map_size, t_player *player,
				t_img *frame);

int	render_next_frame(t_game *game)
{
	t_engine	this;

	if (game->player.exit)
		clean_exit(game);
	apply_changes_on_player(game, &game->player, game->map.real_map);
	draw_floor_and_ceiling(game, game->map, game->player, &game->frame);
	running_animation(&game->player);
	this.pixel = 0;
	while (this.pixel < WIDTH)
	{
		setup_ray(&this, game->player);
		set_distances_to_sides(&game->player, &this);
		dda_find_wall(&this, game->map.real_map);
		calculate_distances_to_wall(&game->player, &this);
		setup_texture(&this, game->textures, &game->player);
		draw_wall_line(&this, &game->player, &game->frame);
		this.pixel++;
	}
	setup_animation_curve(&game->player);
	changing_weapon_animation(&game->player);
	draw_hud_object(game, &game->player);
	draw_map(game->map.real_map, game->map.size, &game->player, &game->frame);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->frame.img, 0, 0);
	return (0);
}

void	draw_map(int **map, t_vector map_size, t_player *player, t_img *frame)
{
	int	i;
	int	j;
	int	square;

	square = WIDTH / (map_size.x * 5);
	i = 0;
	while (i < map_size.y)
	{
		j = 0;
		while (j < map_size.x)
		{
			if (map[i][j] == 0)
				rectangle(frame, new_rectangle(square, square, 0xFFFFFF,
						new_vector(j * square, i * square)));
			else if (map[i][j] == 1)
				rectangle(frame, new_rectangle(square, square, 0x000000,
						new_vector(j * square, i * square)));
			j++;
		}
		i++;
	}
	rectangle(frame, new_rectangle(5, 5, 0xFF0000, new_vector(
				player->position.x * square, player->position.y * square)));
}
