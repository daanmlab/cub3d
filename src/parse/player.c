/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:23:20 by dabalm            #+#    #+#             */
/*   Updated: 2024/02/25 22:10:27 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_vector	filter_initial_direction(char *tmp)
{
	if (*tmp == 'N')
		return (new_vector(0, -1));
	else if (*tmp == 'S')
		return (new_vector(0, 1));
	else if (*tmp == 'E')
		return (new_vector(1, 0));
	return (new_vector(-1, 0));
}

static t_vector	filter_initial_plane(char *tmp)
{
	if (*tmp == 'N')
		return (new_vector(0.66, 0));
	else if (*tmp == 'S')
		return (new_vector(-0.66, 0));
	else if (*tmp == 'E')
		return (new_vector(0, -0.66));
	return (new_vector(0, 0.66));
}

static int	set_player(t_game *game, t_vector pos)
{
	char	*temp;
	char	*direction;

	direction = "NSEW";
	temp = ft_strchr(direction, game->map.matrix[(int)pos.y][(int)pos.x]);
	if (!temp)
		return (0);
	game->player.position.y = pos.y;
	game->player.position.x = pos.x;
	game->player.initial_dir = *temp;
	game->player.dir = filter_initial_direction(temp);
	game->player.plane = filter_initial_plane(temp);
	game->player.map_square = new_vector(floor(pos.x), floor(pos.y));
	return (1);
}

int	find_player(t_game *game)
{
	t_vector	curr;
	int			players_found;

	game->player = player_constructor();
	players_found = 0;
	curr.y = 0;
	while (game->map.matrix[(int)curr.y])
	{
		curr.x = 0;
		while (game->map.matrix[(int)curr.y][(int)curr.x])
		{
			if (set_player(game, curr) == 1)
				players_found++;
			curr.x++;
		}
		curr.y++;
	}
	if (!players_found)
		return (ft_putstr_fd("Error: no player found\n", 2), 0);
	else if (players_found > 1)
		return (ft_putstr_fd("Error: too many players\n", 2), 0);
	return (1);
}

t_player	player_constructor(void)
{
	t_player	new;

	new.mouse_sensibility = 0.006;
	new.last_mouse_x = WIDTH / 2;
	new.last_mouse_y = HEIGHT / 2;
	new.pov_rotation_y_axis = 0.0;
	new.is_walking = false;
	new.is_walking_back = false;
	new.is_walking_left = false;
	new.is_walking_right = false;
	new.is_running = 0;
	new.is_looking_left = false;
	new.is_looking_right = false;
	return (new);
}
