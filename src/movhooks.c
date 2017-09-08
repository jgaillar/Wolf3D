/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgaillar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 02:18:46 by jgaillar          #+#    #+#             */
/*   Updated: 2017/08/03 13:50:38 by jgaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	movement(int keycode, t_stuff *e)
{
	if (keycode == 13)
	{
		if (e->map.array[(int)(e->wolf.posx + e->wolf.dirx * \
			e->wolf.movespeed)][(int)e->wolf.posy] == 0)
			e->wolf.posx += e->wolf.dirx * e->wolf.movespeed;
		if (e->map.array[(int)e->wolf.posx][(int)(e->wolf.posy + \
			e->wolf.diry * e->wolf.movespeed)] == 0)
			e->wolf.posy += e->wolf.diry * e->wolf.movespeed;
	}
	if (keycode == 1)
	{
		if (e->map.array[(int)(e->wolf.posx - e->wolf.dirx * \
			e->wolf.movespeed)][(int)e->wolf.posy] == 0)
			e->wolf.posx -= e->wolf.dirx * e->wolf.movespeed;
		if (e->map.array[(int)e->wolf.posx][(int)(e->wolf.posy - \
			e->wolf.diry * e->wolf.movespeed)] == 0)
			e->wolf.posy -= e->wolf.diry * e->wolf.movespeed;
	}
}

void	right(int keycode, t_stuff *e)
{
	double olddirx;
	double oldplanex;

	if (keycode == 2)
	{
		olddirx = e->wolf.dirx;
		e->wolf.dirx = e->wolf.dirx * cos(-e->wolf.rotspeed) - \
		e->wolf.diry * sin(-e->wolf.rotspeed);
		e->wolf.diry = olddirx * sin(-e->wolf.rotspeed) + \
		e->wolf.diry * cos(-e->wolf.rotspeed);
		oldplanex = e->wolf.planex;
		e->wolf.planex = e->wolf.planex * cos(-e->wolf.rotspeed) - \
		e->wolf.planey * sin(-e->wolf.rotspeed);
		e->wolf.planey = oldplanex * sin(-e->wolf.rotspeed) + \
		e->wolf.planey * cos(-e->wolf.rotspeed);
	}
}

void	left(int keycode, t_stuff *e)
{
	double olddirx;
	double oldplanex;

	if (keycode == 0)
	{
		olddirx = e->wolf.dirx;
		e->wolf.dirx = e->wolf.dirx * cos(e->wolf.rotspeed) - \
		e->wolf.diry * sin(e->wolf.rotspeed);
		e->wolf.diry = olddirx * sin(e->wolf.rotspeed) + \
		e->wolf.diry * cos(e->wolf.rotspeed);
		oldplanex = e->wolf.planex;
		e->wolf.planex = e->wolf.planex * cos(e->wolf.rotspeed) - \
		e->wolf.planey * sin(e->wolf.rotspeed);
		e->wolf.planey = oldplanex * sin(e->wolf.rotspeed) + \
		e->wolf.planey * cos(e->wolf.rotspeed);
	}
}
