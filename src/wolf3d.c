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
#include <stdio.h>

void	wolf3d(t_stuff *stuff)
{
	t_tmp *tmp;
	int i;
	int j;

	i = -1;
	while (++i < MT)
	{
		tmp = malloc(sizeof(t_tmp));
		tmp->start = i * WIDTH / MT;
		tmp->end = tmp->start + WIDTH / MT;
		tmp->stuff = stuff;
		// pthread_create(&stuff->th[i], NULL, \
		// 	(void*(*)(void *))(&draw_wolf), (void *)(tmp));
		draw_wolf(*tmp, &stuff->img);
	}
	j = -1;
	// while (++j < MT)
	// 	pthread_join(stuff->th[j], NULL);
	mlx_put_image_to_window(stuff->img.mlx_ptr, stuff->img.win_ptr, \
		stuff->img.img_ptr, 0, 0);
}

void	draw_wolf(t_tmp tmp, t_img *img)
{
	t_draw	draw;
	t_stuff *stuff;

	stuff = tmp.stuff;
//	printf("%f\n", stuff->wolf.angle);
	draw.angle = 60;
	check_hor(stuff->wolf, &draw, stuff->map);
	// while (tmp.start < tmp.end)
	// {
	// 	if (check_hor(stuff->map, &draw) == 1)
	// 	{
	// 		draw.disthor = draw.dist;
	// 		check_ver(stuff->map, &draw);
	// 		draw.distver = draw.dist;
	// 		draw.dist = (draw.disthor < draw.distver ? draw.disthor : draw.distver);
	// 	//printf("disthor : [%f]\n", draw.dist);
	// 		correc_dist(&draw, stuff);
	// 		aff(&draw, stuff, img, tmp.start);
	// 	}
	// 	draw.angle -= stuff->wolf.angleray;
	// 	tmp.start++;
}

int	check_hor(t_wolf wolf, t_draw *draw, t_map map)
{
	draw->Yi = (draw->angle > 0 && draw->angle <= 180 ? \
		floor(wolf.posy/64) * 64 - 1 : floor(wolf.posy/64) * 64 + 64);
	draw->Xi = floor(wolf.posx + (wolf.posy - draw->Yi) / atan(draw->angle));
	draw->x = floor(draw->Xi / 64);
	draw->y = floor(draw->Yi / 64);
	draw->Ya = (draw->angle > 0 && draw->angle <= 180 ? 64 : -64);
	draw->Xa = floor((draw->Ya / atan(draw->angle)));
	while (draw->y >= 0 && draw->y < map.maxy && draw->x >= 0 && draw->x < map.maxx)
	{
		printf("Yi : [%f]\nXi : [%f]\nx : [%i]\ny : [%i]\nYa : [%f]\nXa : [%f]\n\n", draw->Yi, draw->Xi, draw->x, draw->y, draw->Ya, draw->Xa);
		if (map.array[draw->y][draw->x] == 1)
		{
			ft_putendl("wall");
			draw->dist = fabs(wolf.posx - draw->Xi) / cos(draw->angle);
			return (1);
		}
		else
		{
			draw->Xi += draw->Xa;
			draw->Yi -= draw->Ya;
			draw->x = floor(draw->Xi / 64);
			draw->y = floor(draw->Yi / 64);
		}
	}
	return (0);
}

// int	check_ver(t_wolf wolf, t_draw *draw, t_map map)
// {
//
// }

void	correc_dist(t_draw *draw, t_stuff *stuff)
{
	double	angle;

	angle = ((stuff->wolf.angle - draw->angle) * -1);
	draw->dist = draw->dist * acos(cos(angle));
}

void	aff(t_draw *draw, t_stuff *stuff, t_img *img, int x)
{
	double	height;
	int		tmp;
	int i;

	height = floor((64/draw->dist * stuff->wolf.dispw));
	tmp = (WIDTH / 2) - (height / 2);
	i = tmp;
	mlx_pixel_put_to_image(*img, x, 0, 0xFFFFFF - (0.1 * i));
	while (i++ < tmp + height)
		mlx_pixel_put_to_image(*img, x, i, 0xFFFFFF - (0.1 * i));
}
