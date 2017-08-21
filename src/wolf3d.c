/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgaillar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 13:09:10 by jgaillar          #+#    #+#             */
/*   Updated: 2017/08/21 13:09:11 by jgaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	wolf3d(t_stuff *stuff)
{
	t_tmp *tmp;

	stuff->i = -1;
	while (++stuff->i < MT)
	{
		tmp = malloc(sizeof(t_tmp));
		tmp->start = stuff->i * WIDTH / MT;
		tmp->end = tmp->start + WIDTH / MT;
		tmp->stuff = stuff;
		pthread_create(&stuff->th[stuff->i], NULL, \
			(void*(*)(void *))(&draw_wolf), (void *)(tmp));
	}
	stuff->j = -1;
	while (++stuff->j < MT)
		pthread_join(stuff->th[stuff->j], NULL);
	mlx_put_image_to_window(stuff->img.mlx_pr, stuff->img.win_ptr, \
		stuff->img.img_ptr, 0, 0);
}

void	draw_wolf(t_tmp *tmp)
{
	t_draw	draw;
	double	disthor;
	double	distver;

	draw.angle = stuff->wolf.angle - 30;
	while (++tmp->start < tmp->end)
	{
		check_hor(tmp, &draw);
		draw.disthor = draw.dist;
		check_ver(tmp, &draw);
		draw.distver = draw.dist;
		draw.dist = (draw.disthor > draw.distver ? draw.distver : draw.disthor);
	}
}

void	check_hor(t_tmp *tmp, t_draw *draw)
{
	draw->Ya = (draw->angle > 0 && draw->angle < 180 ? -64 : 64);
	draw->Xa = stuff->wolf->wallh/tan(draw->angle);
	draw->Yi = (draw->angle > 0 && draw->angle < 180 ? \
		floor((stuff->wolf.posy/stuff->wolf.wallh) * (stuff->wolf.wallh) - 1) : \
		floor((stuff->wokf.posy/stuff->wokf.wallh) * (stuff->wolf.wallh) + \
		stuff->wolf.wallh));
	draw->Xi = stuff->wolf.posx + (stuff->wolf.posy - draw->Yi)/tan(draw->angle);
	draw->x = draw->Xi / stuff->wolf.wallh;
	draw->y = draw->Yi / stuff->wolf.wallh;
	while (stuff->map.array[draw->y][draw->x] == 0)
	{
		draw->Yi += draw.Ya;
		draw->Xi += draw.Xa;
		draw->x = floor(draw->Xi / stuff->wolf.wallh);
		draw->y = floor(draw->Yi / stuff->wolf.wallh);
	}
	draw->dist = abs(stuff->wolf.posx - draw->Xi) / cos(draw->angle);
}

void	check_ver(t_tmp *tmp, t_draw *draw)
{
	draw->Ya = stuff->wolf.wallh * tan(draw->angle);
	draw->Xa = (draw->angle > 90 && dra->angle < 270 ? -64 : 64);
	draw->Yi = stuff->wolf.posy + (stuff->wolf.posx - draw.Xa) * tan(draw.angle);
	draw->Xi = (draw->angle > 90 && dra->angle < 270 ? \
		floor(stuff->wolf.posx/stuff->wolf.wallh) * stuff->wolf.wallh - 1 :
		floor(stuff->wolf.posx/stuff->wolf.wallh) * stuff->wolf.wallh \
		+ stuff->wolf.wallh);
	draw->x = draw->Xi / stuff->wolf.wallh;
	draw->y = draw->Yi / stuff->wolf.wallh;
	while (stuff->map.array[draw->y][draw->x] == 0)
	{
		draw->Yi += draw.Ya;
		draw->Xi += draw.Xa;
		draw->x = floor(draw->Xi / stuff->wolf.wallh);
		draw->y = floor(draw->Yi / stuff->wolf.wallh);
	}
	draw->dist = abs(stuff->wolf.posx - draw->Xi) / cos(draw->angle);
}
