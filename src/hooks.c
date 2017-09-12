/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgaillar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 14:14:47 by jgaillar          #+#    #+#             */
/*   Updated: 2017/09/07 14:14:48 by jgaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		hooks(int keycode, t_stuff *e)
{
	echap(keycode, e);
	movement(keycode, e);
	right(keycode, e);
	left(keycode, e);
	return (0);
}

void	echap(int keycode, t_stuff *e)
{
	int i;

	i = -1;
	if (keycode == 53)
    {
		while (++i < e->map.maxy)
			free(e->map.array[i]);
		free(e->map.array);
		free(e->img.data);
		mlx_destroy_image(e->img.mlx_ptr, e->img.win_ptr);
		exit(0);
    }
}

void	cleanexit(t_stuff *e)
{
	int i;

	i = -1;
	while (++i < e->map.maxy)
		free(e->map.array[i]);
	free(e->map.array);
	free(e->img.data);
	mlx_destroy_image(e->img.mlx_ptr, e->img.win_ptr);
	exit(0);
}
