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

void	init_struct(t_stuff *stuff)
{
	if (!(stuff->th = (pthread_t *)malloc(sizeof(pthread_t) * MT)))
		exit(0);
	stuff->map.maxx = linelength(stuff->buf) + 2;
	stuff->map.maxy = lentab(stuff->buf) + 2;
	stuff->map.array = malloc2d(&stuff->map);
	stuff->wolf.posX = 6.5;
	stuff->wolf.posY = 6.5;
	stuff->wolf.dirX = -1;
	stuff->wolf.dirY= 0;
	stuff->wolf.planeX = 0;
	stuff->wolf.planeY = 0.66;
	stuff->wolf.hit = 0;
	stuff->map.x = -1;
	putintab(stuff);
	create_image(stuff);
}

void	create_image(t_stuff *stuff)
{
	stuff->img.img_ptr = mlx_new_image(stuff->img.mlx_ptr, WIDTH, LENGTH);
	if (!(stuff->img.data = (char *)ft_strnew(sizeof(char)\
		* WIDTH * LENGTH * 4)))
		exit(0);
	stuff->img.data = mlx_get_data_addr(stuff->img.img_ptr,\
		&stuff->img.bits_per_pixel, &stuff->img.size_line, &stuff->img.endian);
}
