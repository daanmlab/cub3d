/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:23:20 by dabalm            #+#    #+#             */
/*   Updated: 2024/02/15 17:18:12 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int set_player(t_game* game, struct s_position pos, char **found)
{
    char *temp;
    char *direction;
    
    direction = "NSEW";

    temp = ft_strchr(direction, game->map.matrix[pos.y][pos.x]);
    if (*found && temp)
        return (ft_printf("too many players") && 0);
    if (temp)
    {
        *found = temp;
        game->player.initial_postion.y = pos.y;
        game->player.initial_postion.x = pos.x;
        game->player.initial_direction = *direction;
    }
    return 1;
}

int find_player(t_game* game)
{
    struct s_position curr;
    char *found;

    curr.y = 0;
    found = NULL;
    while (game->map.matrix[curr.y])
    {
        curr.x = 0;
        while (game->map.matrix[curr.y][curr.x])
        {
            if (!set_player(game, curr, &found))
                return 0;
            curr.x++;
        }
        curr.y++;
    }
    if (!found)
        return (ft_printf("no player found") && 0);
    return 1;
}

int get_player(t_game *game)
{
    return find_player(game);
}