/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:41:50 by dabalm            #+#    #+#             */
/*   Updated: 2024/02/26 20:19:38 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_color(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_strchr("0123456789 ,", str[i]))
		i++;
	return (!str[i]);
}

int	extract_color(const char *temp, t_color *color)
{
	char	**split;
	char	*str;
	int		i;

	str = ft_strtrim(temp, "\n ");
	i = 0;
	if (!is_color(str))
		return (free(str), ft_putstr_fd("invalid color.\n", 2), 0);
	split = ft_split(str, ',');
	while (split[i])
		i++;
	if (i != 3)
		return ((ft_putstr_fd("invalid color.\n", 2), free(str), 0)
			&& ft_free_tab(split));
	color->r = ft_atoi(split[0]);
	color->g = ft_atoi(split[1]);
	color->b = ft_atoi(split[2]);
	ft_free_tab(split);
	if (color->r > 255 || color->g > 255 || color->b > 255)
		return (ft_putstr_fd("invalid color.\n", 2), free(str), 0);
	color->color = color->r;
	color->color = (color->color << 8) + color->g;
	color->color = (color->color << 8) + color->b;
	free(str);
	return (1);
}

int	set_color(const char *line, t_game *game)
{
	char	**split;
	int		i;

	split = ft_split(line, ' ');
	i = 0;
	while (split && split[i])
		i++;
	if (i != 2)
		return (!!ft_free_tab(split));
	if (!ft_strncmp(split[0], "F", 2))
		game->floor_color.error = !extract_color(split[1], &game->floor_color);
	else if (!ft_strncmp(split[0], "C", 2))
		game->ceiling_color.error = !extract_color(split[1],
				&game->ceiling_color);
	else
		return (!!ft_free_tab(split));
	ft_free_tab(split);
	return (1);
}

int	get_colors(int fd, t_game *game)
{
	char	*line;

	line = get_next_line(fd);
	game->floor_color.error = 1;
	game->ceiling_color.error = 1;
	while (set_color(line, game))
	{
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (!game->ceiling_color.error && !game->floor_color.error);
}
