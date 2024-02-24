/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:10:27 by dabalm            #+#    #+#             */
/*   Updated: 2024/02/24 01:27:11 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char const *argv[])
{
	t_game	game;

	game.mlx = mlx_init();
	ft_printf("\033[0m");
	if (parse(argc, argv, &game))
		ft_printf("great success\n");
	game.mlx_win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "cub3d");
	game.frame.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	game.frame.addr = mlx_get_data_addr(game.frame.img, &game.frame.bits_per_pixel, &game.frame.line_length, &game.frame.endian);
	mlx_loop_hook(game.mlx, &engine, &game);
	mlx_loop(game.mlx);
	// free_textures(&game);
	mlx_destroy_display(game.mlx);
	free(game.mlx);
	return (0);
}
