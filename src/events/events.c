/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 22:05:38 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/02/24 14:34:25 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int catch_key_press(int key, t_player *player)
{
	if (key == XK_w)
		player->is_walking = true;
	if (key == XK_s)
		player->is_walking_back = true;
	if (key == XK_Left)
		player->is_looking_left = true;
	return (0);
}

int catch_key_release(int key, t_player *player)
{
	if (key == XK_w)
		player->is_walking = false;
	if (key == XK_s)
		player->is_walking_back = false;
	if (key == XK_Left)
		player->is_looking_left = false;
	return (0);
}
