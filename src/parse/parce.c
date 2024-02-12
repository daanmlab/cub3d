/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabalm <dabalm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:46:23 by dabalm            #+#    #+#             */
/*   Updated: 2024/02/12 18:08:58 by dabalm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <sys/stat.h>
#include <fcntl.h>

void *free_tab(char **tab)
{
    static int i;

    while (tab[i])
        free(tab[i++]);
    free(tab);
    return NULL;
}

int check_file_name(const char *filename)
{
    char **split;
    static int result;
    static int i;

    split = ft_split(filename, '.');
    while (split[i])
        i++;
    i--;
    result = !ft_strncmp(split[i], "cub", ft_strlen(split[i]));
    while (i >= 0)
        free(split[i--]);
    free(split);
    return (result);
}

int check_args(int argc, char const *argv[])
{
    if (argc < 2)
        return (ft_printf("not enough arguments\n") && 0);
    if (argc > 2)
        return (ft_printf("too many arguments\n") && 0);
    if (!check_file_name(argv[1]))
        return (ft_printf("invalid file name\n") && 0);
    return (1);
}

int set_texture(const char *line, t_map *map)
{
    char **split;
    int i;

    split = ft_split(line, ' ');
    i = 0;
    while (split && split[i])
        i++;
    if (i != 2)
        return !!free_tab(split);
    if (ft_strncmp(split[0], "NO", 3))
        map->north_texture = split[1];
    else if (ft_strncmp(split[0], "SO", 3))
        map->south_texture = split[1];
    else if (ft_strncmp(split[0], "WE", 3))
        map->west_texture = split[1];
    else if (ft_strncmp(split[0], "EA", 3))
        map->east_texture = split[1];
    else
        return !!free_tab(split);
    free(split[0]);
    free(split);
    return (1);
}

// int check_textures(t_game *game)
// {
    
// }

int get_textures(int fd, t_map *map)
{
    char *line;

    line = get_next_line(fd);
    while (set_texture(line, map))
    {
        free(line);   
        line = get_next_line(fd);
    }
    free(line);
    return 1;
}

int parse(int argc, char const *argv[], t_game *game)
{
    int fd;
    
    if (!check_args(argc, argv))
        return 0;
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        return (ft_printf("file doesn't exist\n") && 0);
    get_textures(fd, &(game->map));
        
    ft_printf("game: %p", game);
    return 1;
}
