/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:10:27 by dabalm            #+#    #+#             */
/*   Updated: 2024/02/15 17:07:00 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char const *argv[])
{
	struct s_game	game;

	game.mlx = mlx_init();
	ft_printf("\033[0m");
	if (parse(argc, argv, &game))
		ft_printf("great success\n");
	// free_textures(&game);
	mlx_destroy_display(game.mlx);
	free(game.mlx);
	return (0);
}
