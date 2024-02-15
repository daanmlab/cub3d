/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 21:52:14 by tlouro-c          #+#    #+#             */
/*   Updated: 2024/02/15 22:00:37 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector	new_vector(double x, double y)
{
	t_vector	new;

	new.x = x;
	new.y = y;
	return (new);
}

t_vector	v_sum(t_vector v1, t_vector v2)
{
	return (new_vector(v1.x + v2.x, v1.y + v2.y));
}

t_vector	v_mult(t_vector v1, t_vector v2)
{
	return (new_vector(v1.x * v2.x, v1.y * v2.y));
}

t_vector	v_normalize(t_vector v)
{
	double	magnitude;

	magnitude = sqrt(v.x * v.x + v.y * v.y);
	return (new_vector(v.x / magnitude, v.y / magnitude));
}

t_vector	v_rotate(t_vector v, double angle)
{
	t_vector	new;

	new.x = v.x * cos(angle) - v.y * sin(angle);
	new.y = v.x * sin(angle) + v.y * cos(angle);
	return (new);
}

