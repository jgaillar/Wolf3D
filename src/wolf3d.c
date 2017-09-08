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

void	fps_counter(t_stuff *e)
{
	struct timeval	tp;
	char			*tmp;

	e->wolf.oldtime = e->wolf.time;
	gettimeofday(&tp, NULL);
	e->wolf.time = tp.tv_usec;
	gettimeofday(&tp, NULL);
	e->wolf.time = tp.tv_usec;
	e->wolf.frametime = round((e->wolf.time - e->wolf.oldtime) / 1000);
	if (e->wolf.frametime < 0)
		fps_counter(e);
	tmp = ft_itoa((int)e->wolf.frametime);
	mlx_string_put(e->img.mlx_ptr, e->img.win_ptr, \
		WIDTH / 100, LENGTH / 100, 0xFFFFFF, tmp);
	free(tmp);
	e->wolf.movespeed = e->wolf.frametime * 0.003;
	e->wolf.rotspeed = e->wolf.frametime * 0.003;
}

void	wolf3d(t_stuff *e)
{
	e->map.x = -1;
	while (++e->map.x < WIDTH)
	{
		e->wolf.camerax = 2 * e->map.x / (float)WIDTH - 1;
		e->wolf.rayposx = e->wolf.posx;
		e->wolf.rayposy = e->wolf.posy;
		e->wolf.raydirx = e->wolf.dirx + e->wolf.planex * \
			e->wolf.camerax;
		e->wolf.raydiry = e->wolf.diry + e->wolf.planey * \
			e->wolf.camerax;
		e->wolf.mapx = (int)e->wolf.rayposx;
		e->wolf.mapy = (int)e->wolf.rayposy;
		e->wolf.deltadistx = sqrt(1 + (e->wolf.raydiry * \
			e->wolf.raydiry) / (e->wolf.raydirx * e->wolf.raydirx));
		e->wolf.deltadisty = sqrt(1 + (e->wolf.raydirx * \
			e->wolf.raydirx) / (e->wolf.raydiry * e->wolf.raydiry));
		setdir(e);
		dda(e);
		distance_calcultor(e);
		aff(e);
	}
	mlx_put_image_to_window(e->img.mlx_ptr, e->img.win_ptr, \
		e->img.img_ptr, 0, 0);
	fps_counter(e);
}

void	setdir(t_stuff *e)
{
	if (e->wolf.raydirx < 0)
	{
		e->wolf.stepx = -1;
		e->wolf.sidedistx = (e->wolf.rayposx - e->wolf.mapx) *\
			e->wolf.deltadistx;
	}
	else
	{
		e->wolf.stepx = 1;
		e->wolf.sidedistx = (e->wolf.mapx + 1 - e->wolf.rayposx)
			* e->wolf.deltadistx;
	}
	if (e->wolf.raydiry < 0)
	{
		e->wolf.stepy = -1;
		e->wolf.sidedisty = (e->wolf.rayposy - e->wolf.mapy) * \
			e->wolf.deltadisty;
	}
	else
	{
		e->wolf.stepy = 1;
		e->wolf.sidedisty = (e->wolf.mapy + 1 - e->wolf.rayposy)
			* e->wolf.deltadisty;
	}
}

void	dda(t_stuff *e)
{
	e->wolf.hit = 0;
	while (e->wolf.hit == 0)
	{
		if (e->wolf.sidedistx < e->wolf.sidedisty)
		{
			e->wolf.sidedistx += e->wolf.deltadistx;
			e->wolf.mapx += e->wolf.stepx;
			e->wolf.side = 0;
		}
		else
		{
			e->wolf.sidedisty += e->wolf.deltadisty;
			e->wolf.mapy += e->wolf.stepy;
			e->wolf.side = 1;
		}
		if (e->map.array[e->wolf.mapx][e->wolf.mapy] > 0)
			e->wolf.hit = 1;
	}
}

void	distance_calcultor(t_stuff *e)
{
	if (e->wolf.side == 0)
		e->draw.perpwalldist = (e->wolf.mapx - e->wolf.rayposx\
			+ (1 - e->wolf.stepx) / 2) / e->wolf.raydirx;
	else
		e->draw.perpwalldist = (e->wolf.mapy - e->wolf.rayposy\
			+ (1 - e->wolf.stepy) / 2) / e->wolf.raydiry;
	e->draw.lineheight = (LENGTH / e->draw.perpwalldist);
	e->draw.start = -e->draw.lineheight / 2 + LENGTH / 2;
	if (e->draw.start < 0)
		e->draw.start = 0;
	e->draw.end = e->draw.lineheight / 2 + LENGTH / 2;
	if (e->draw.end >= LENGTH)
		e->draw.end = LENGTH - 1;
}
