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
	draw_wolf(stuff);
	mlx_put_image_to_window(stuff->img.mlx_ptr, stuff->img.win_ptr, \
		stuff->img.img_ptr, 0, 0);
}

void	draw_wolf(t_stuff *stuff)
{
	stuff->map.x = -1;
	while (++stuff->map.x < WIDTH)
	{
		stuff->wolf.cameraX = 2 * stuff->map.x / WIDTH - 1;
		stuff->wolf.rayPosX = stuff->wolf.posX;
		stuff->wolf.rayPosY = stuff->wolf.posY;
		stuff->wolf.rayDirX = stuff->wolf.dirX + stuff->wolf.planeX * \
			stuff->wolf.cameraX;
		stuff->wolf.rayDirY = stuff->wolf.dirY + stuff->wolf.planeY * \
			stuff->wolf.cameraX;
		stuff->wolf.mapX = stuff->wolf.rayPosX;
		stuff->wolf.mapY = stuff->wolf.rayPosY;
		stuff->wolf.deltaDistX = sqrt(1 + (stuff->wolf.rayDirY * \
			stuff->wolf.rayDirY) / (stuff->wolf.rayDirX * stuff->wolf.rayDirX));
		stuff->wolf.deltaDistX = sqrt(1 + (stuff->wolf.rayDirX * \
			stuff->wolf.rayDirX) / (stuff->wolf.rayDirY * stuff->wolf.rayDirY));
		setdir(stuff);
		dda(stuff);
		distance_calcultor(stuff);
		aff(stuff);
	}
}

void	setdir(t_stuff *stuff)
{
		if (stuff->wolf.rayDirX < 0)
		{
			stuff->wolf.stepX = -1;
			stuff->wolf.sideDistX = (stuff->wolf.rayPosX - stuff->wolf.mapX) *\
				stuff->wolf.deltaDistX;
		}
		else
		{
			stuff->wolf.stepX = 1;
			stuff->wolf.sideDistX = (stuff->wolf.mapX + 1 - stuff->wolf.rayPosX)
				* stuff->wolf.deltaDistX;
		}
		if (stuff->wolf.rayDirY < 0)
		{
			stuff->wolf.stepY = -1;
			stuff->wolf.sideDistY = (stuff->wolf.rayPosY - stuff->wolf.mapY) * \
				stuff->wolf.deltaDistY;
		}
		else
		{
			stuff->wolf.stepY = 1;
			stuff->wolf.sideDistY = (stuff->wolf.mapY + 1 - stuff->wolf.rayPosY)
				* stuff->wolf.deltaDistY;
		}
}

void	dda(t_stuff *stuff)
{
	while (stuff->wolf.hit == 0)
	{
		if (stuff->wolf.sideDistX < stuff->wolf.sideDistY)
		{
			stuff->wolf.sideDistX += stuff->wolf.deltaDistX;
			stuff->wolf.mapX += stuff->wolf.stepX;
			stuff->wolf.side = 0;
		}
		else
		{
			stuff->wolf.sideDistY += stuff->wolf.deltaDistY;
			stuff->wolf.mapY += stuff->wolf.stepY;
			stuff->wolf.side = 1;
		}
		if (stuff->map.array[stuff->wolf.mapY][stuff->wolf.mapY] > 0)
			stuff->wolf.hit = 1;
	}
}

void	distance_calcultor(t_stuff *stuff)
{
	if (stuff->wolf.side == 0)
		stuff->draw.perpWallDist = (stuff->wolf.mapX - stuff->wolf.rayPosX\
			+ (1 - stuff->wolf.stepX) / 2) / stuff->wolf.rayDirX;
	else
		stuff->draw.perpWallDist = (stuff->wolf.mapY - stuff->wolf.rayPosY\
			+ (1 - stuff->wolf.stepY) / 2) / stuff->wolf.rayDirY;
	stuff->draw.lineHeight = LENGTH / stuff->draw.perpWallDist;
	stuff->draw.start = -stuff->draw.lineHeight / 2 + LENGTH / 2;
	if (stuff->draw.start < 0)
		stuff->draw.start = 0;
	stuff->draw.end = stuff->draw.lineHeight / 2 + LENGTH / 2;
	if (stuff->draw.end >= LENGTH)
		stuff->draw.end = LENGTH - 1;
}

void	aff(t_stuff *stuff)
{
	int i;
	int j;

	i = -1;
	j = stuff->draw.start - 1;
	while (++i < stuff->draw.start)
		mlx_pixel_put_to_image(stuff->img, stuff->map.x, i, 0x00FFFF);
	while (++j < stuff->draw.end)
		mlx_pixel_put_to_image(stuff->img, stuff->map.x, j, 0xFF0000);
}
