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

int		hooks(int keycode, t_stuff *stuff)
{
	echap(keycode, stuff);
	movement(keycode, stuff);
	rotation(keycode, stuff);
	return (0);
}

void	echap(int keycode, t_stuff *stuff)
{
	if (keycode == 53)
		exit(0);
}

void	cleanexit(t_stuff *stuff)
{
	free(stuff->map.array);
	exit(0);
}

void	movement(int keycode, t_stuff *stuff)
{
	if (keycode == 126)
	{
		printf("posX : [%f]\n", (stuff->wolf.posX + stuff->wolf.dirX * stuff->wolf.moveSpeed));
		if (stuff->map.array[(int)(stuff->wolf.posX + stuff->wolf.dirX * stuff->wolf.moveSpeed)][(int)stuff->wolf.posY] == 0)
			stuff->wolf.posX += stuff->wolf.dirX * stuff->wolf.moveSpeed;
		if (stuff->map.array[(int)stuff->wolf.posX][(int)(stuff->wolf.posY + stuff->wolf.dirY * stuff->wolf.moveSpeed)] == 0)
			stuff->wolf.posY += stuff->wolf.dirY * stuff->wolf.moveSpeed;
	}
	if (keycode == 125)
	{
		printf("posX : [%f]\n", (stuff->wolf.posX - stuff->wolf.dirX * stuff->wolf.moveSpeed));
		if (stuff->map.array[(int)(stuff->wolf.posX - stuff->wolf.dirX * stuff->wolf.moveSpeed)][(int)stuff->wolf.posY] == 0)
			stuff->wolf.posX -= stuff->wolf.dirX * stuff->wolf.moveSpeed;
		if (stuff->map.array[(int)stuff->wolf.posX][(int)(stuff->wolf.posY - stuff->wolf.dirY * stuff->wolf.moveSpeed)] == 0)
			stuff->wolf.posY -= stuff->wolf.dirY * stuff->wolf.moveSpeed;
	}
}

static void	rotation(int keycode, t_stuff *stuff)
{
	double oldDirX;
	double oldPlaneX;

	if (keycode == 124)
	{
		oldDirX = stuff->wolf.dirX;
		stuff->wolf.dirX = stuff->wolf.dirX * cos(-stuff->wolf.rotSpeed) - stuff->wolf.dirY * sin(-stuff->wolf.rotSpeed);
		stuff->wolf.dirY = oldDirX * sin(-stuff->wolf.rotSpeed) + stuff->wolf.dirY * cos(-stuff->wolf.rotSpeed);
		oldPlaneX = stuff->wolf.planeX;
		stuff->wolf.planeX = stuff->wolf.planeX * cos(-stuff->wolf.rotSpeed) - stuff->wolf.planeY * sin(-stuff->wolf.rotSpeed);
		stuff->wolf.planeY = oldPlaneX * sin(-stuff->wolf.rotSpeed) + stuff->wolf.planeY * cos(-stuff->wolf.rotSpeed);
	}
	if (keycode == 123)
	{
		oldDirX = stuff->wolf.dirX;
		stuff->wolf.dirX = stuff->wolf.dirX * cos(stuff->wolf.rotSpeed) - stuff->wolf.dirY * sin(stuff->wolf.rotSpeed);
		stuff->wolf.dirY = oldDirX * sin(stuff->wolf.rotSpeed) + stuff->wolf.dirY * cos(stuff->wolf.rotSpeed);
		printf("dirX : [%f] dirY  [%f]\n", stuff->wolf.dirX, stuff->wolf.dirY);
		oldPlaneX = stuff->wolf.planeX;
		stuff->wolf.planeX = stuff->wolf.planeX * cos(stuff->wolf.rotSpeed) - stuff->wolf.planeY * sin(stuff->wolf.rotSpeed);
		stuff->wolf.planeY = oldPlaneX * sin(stuff->wolf.rotSpeed) + stuff->wolf.planeY * cos(stuff->wolf.rotSpeed);
	}
}
