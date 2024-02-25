/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:57:03 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/02/25 21:15:48 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_mouse_x(t_game *game)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(game->mlx, game->mlx_win, &x, &y);
	return (x);
}

int	get_mouse_y(t_game *game)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(game->mlx, game->mlx_win, &x, &y);
	return (y);
}
