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
	init_wolf(stuff);
	putintab(stuff);
	create_image(stuff);
	wolf3d(stuff);
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

void	init_wolf(t_stuff *stuff)
{
	stuff->wolf.wallh = 64;
	stuff->wolf.playerh = stuff->wolf.wallh/2;
	stuff->wolf.posx = 96;
	stuff->wolf.posy = 224;
	stuff->wolf.fov = 60;
	stuff->wolf.angle = 90;
	stuff->wolf.dispw = ((WIDTH/2)/tan(stuff->wolf.fov/2));
	stuff->wolf.angleray = stuff->wolf.fov/WIDTH;
}
