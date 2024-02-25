/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:10:27 by dabalm            #+#    #+#             */
/*   Updated: 2024/02/25 16:16:52 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char const *argv[])
{
	t_game	game;

	game.mlx = mlx_init();
	ft_printf("\033[0m");
	if (!parse(argc, argv, &game))
		return (1);
	game.mlx_win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "cub3d");
	//mlx_mouse_hide(game.mlx, game.mlx_win);
	mlx_do_key_autorepeatoff(game.mlx);
	game.frame.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	game.frame.addr = mlx_get_data_addr(game.frame.img, &game.frame.bits_per_pixel, &game.frame.line_length, &game.frame.endian);
	event_listener(&game);
	mlx_loop_hook(game.mlx, &render_next_frame, &game);
	mlx_loop(game.mlx);
	// free_textures(&game);
	clean_exit(&game);
	return (0);
}
