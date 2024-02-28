/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:10:27 by dabalm            #+#    #+#             */
/*   Updated: 2024/02/26 21:40:40 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char const *argv[])
{
	t_game	game;

	game = game_constructor();
	game.mlx = mlx_init();
	if (parse(argc, argv, &game) == -1)
		return (clean_exit(&game), 1);
	if (setup_window(&game) == -1)
		return (clean_exit(&game), 1);
	mlx_mouse_hide(game.mlx, game.mlx_win);
	event_listener(&game);
	mlx_loop_hook(game.mlx, &render_next_frame, &game);
	mlx_loop(game.mlx);
	clean_exit(&game);
	return (0);
}
