/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgaillar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 13:09:32 by jgaillar          #+#    #+#             */
/*   Updated: 2017/08/08 13:09:33 by jgaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_struct(t_stuff *e)
{
	e->map.maxx = searchbigline(e->buf) + 2;
	e->map.maxy = lentab(e->buf) + 2;
	e->map.array = malloc2d(&e->map);
	e->wolf.dirx = -1;
	e->wolf.diry = 0;
	e->wolf.planex = 0;
	e->wolf.planey = 0.66;
	e->wolf.hit = 0;
	e->map.x = -1;
	putintab(e);
	create_image(e);
	check(e);
}

void	create_image(t_stuff *e)
{
	e->img.img_ptr = mlx_new_image(e->img.mlx_ptr, WIDTH, LENGTH);
	if (!(e->img.data = (char *)ft_strnew(sizeof(char)\
		* WIDTH * LENGTH * 4)))
		exit(0);
	e->img.data = mlx_get_data_addr(e->img.img_ptr,\
		&e->img.bits_per_pixel, &e->img.size_line, &e->img.endian);
}

int		check(t_stuff *e)
{
	int i;
	int j;

	i = -1;
	while (++i < e->map.maxy)
	{
		j = -1;
		while (++j < e->map.maxx)
		{
			if (e->map.array[i][j] == 0)
			{
				e->wolf.posx = i + 0.5;
				e->wolf.posy = j + 0.5;
				return (1);
			}
		}
	}
	return (0);
}
