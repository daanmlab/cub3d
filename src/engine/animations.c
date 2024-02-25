/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 18:09:39 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/02/25 18:10:51 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	running_animation(t_player *player)
{
	if (player->is_running == 2 && v_magnitude(player->plane) < 0.68)
		player->plane = v_mult(player->plane, 1.0009);
	else if (player->is_running != 2 && v_magnitude(player->plane) > 0.66)
		player->plane = v_mult(player->plane, 0.9991);
}
