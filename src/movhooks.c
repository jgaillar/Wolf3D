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

void	movement(int keycode, t_stuff *stuff)
{
	if (keycode == 13)
	{
		if (stuff->map.array[(int)(stuff->wolf.posX + stuff->wolf.dirX * \
			stuff->wolf.moveSpeed)][(int)stuff->wolf.posY] == 0)
			stuff->wolf.posX += stuff->wolf.dirX * stuff->wolf.moveSpeed;
		if (stuff->map.array[(int)stuff->wolf.posX][(int)(stuff->wolf.posY + \
			stuff->wolf.dirY * stuff->wolf.moveSpeed)] == 0)
			stuff->wolf.posY += stuff->wolf.dirY * stuff->wolf.moveSpeed;
	}
	if (keycode == 1)
	{
		if (stuff->map.array[(int)(stuff->wolf.posX - stuff->wolf.dirX * \
			stuff->wolf.moveSpeed)][(int)stuff->wolf.posY] == 0)
			stuff->wolf.posX -= stuff->wolf.dirX * stuff->wolf.moveSpeed;
		if (stuff->map.array[(int)stuff->wolf.posX][(int)(stuff->wolf.posY - \
			stuff->wolf.dirY * stuff->wolf.moveSpeed)] == 0)
			stuff->wolf.posY -= stuff->wolf.dirY * stuff->wolf.moveSpeed;
	}
}

void	right(int keycode, t_stuff *stuff)
{
	double oldDirX;
	double oldPlaneX;

	if (keycode == 2)
	{
		oldDirX = stuff->wolf.dirX;
		stuff->wolf.dirX = stuff->wolf.dirX * cos(-stuff->wolf.rotSpeed) - \
		stuff->wolf.dirY * sin(-stuff->wolf.rotSpeed);
		stuff->wolf.dirY = oldDirX * sin(-stuff->wolf.rotSpeed) + \
		stuff->wolf.dirY * cos(-stuff->wolf.rotSpeed);
		oldPlaneX = stuff->wolf.planeX;
		stuff->wolf.planeX = stuff->wolf.planeX * cos(-stuff->wolf.rotSpeed) - \
		stuff->wolf.planeY * sin(-stuff->wolf.rotSpeed);
		stuff->wolf.planeY = oldPlaneX * sin(-stuff->wolf.rotSpeed) + \
		stuff->wolf.planeY * cos(-stuff->wolf.rotSpeed);
	}
}

void				left(int keycode, t_stuff *stuff)
{
	double oldDirX;
	double oldPlaneX;

	if (keycode == 0)
	{
		oldDirX = stuff->wolf.dirX;
		stuff->wolf.dirX = stuff->wolf.dirX * cos(stuff->wolf.rotSpeed) - \
		stuff->wolf.dirY * sin(stuff->wolf.rotSpeed);
		stuff->wolf.dirY = oldDirX * sin(stuff->wolf.rotSpeed) + \
		stuff->wolf.dirY * cos(stuff->wolf.rotSpeed);
		printf("dirX : [%f] dirY  [%f]\n", stuff->wolf.dirX, stuff->wolf.dirY);
		oldPlaneX = stuff->wolf.planeX;
		stuff->wolf.planeX = stuff->wolf.planeX * cos(stuff->wolf.rotSpeed) - \
		stuff->wolf.planeY * sin(stuff->wolf.rotSpeed);
		stuff->wolf.planeY = oldPlaneX * sin(stuff->wolf.rotSpeed) + \
		stuff->wolf.planeY * cos(stuff->wolf.rotSpeed);
	}
}
