/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:23:20 by dabalm            #+#    #+#             */
/*   Updated: 2024/02/23 21:00:38 by tlouro-c         ###   ########.fr       */
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
	game->player.direction = filter_initial_direction(temp);
	return (1);
}

int	find_player(t_game *game)
{
	t_vector	curr;
	int			players_found;

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
		return (write(2, "Error: no player found\n", 23), 0);
	else if (players_found > 1)
		return (write(2, "Error: too many players\n", 24), 0);
	return (1);
}
