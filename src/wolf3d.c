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

void	fps_counter(t_stuff *stuff)
{
	struct	timeval tp;
	char	*tmp;

	stuff->wolf.oldtime = stuff->wolf.time;
	gettimeofday(&tp, NULL);
	stuff->wolf.time = tp.tv_usec;
	gettimeofday(&tp, NULL);
	stuff->wolf.time = tp.tv_usec;
	stuff->wolf.frameTime = floor((stuff->wolf.time - stuff->wolf.oldtime) / 1000);
	if (stuff->wolf.frameTime < 0)
		fps_counter(stuff);
	tmp = ft_itoa((int)stuff->wolf.frameTime);
	mlx_string_put(stuff->img.mlx_ptr, stuff->img.win_ptr, \
		WIDTH/100,LENGTH/100, 0xFFFFFF, tmp);
	free(tmp);
	stuff->wolf.moveSpeed = stuff->wolf.frameTime * 0.003;
	stuff->wolf.rotSpeed = stuff->wolf.frameTime * 0.003;
}

void	wolf3d(t_stuff *stuff)
{
	stuff->map.x = -1;
	while (++stuff->map.x < WIDTH)
	{
		stuff->wolf.cameraX = 2 * stuff->map.x / (float)WIDTH - 1;
		stuff->wolf.rayPosX = stuff->wolf.posX;
		stuff->wolf.rayPosY = stuff->wolf.posY;
		stuff->wolf.rayDirX = stuff->wolf.dirX + stuff->wolf.planeX * \
			stuff->wolf.cameraX;
		stuff->wolf.rayDirY = stuff->wolf.dirY + stuff->wolf.planeY * \
			stuff->wolf.cameraX;
		stuff->wolf.mapX = (int)stuff->wolf.rayPosX;
		stuff->wolf.mapY = (int)stuff->wolf.rayPosY;
		stuff->wolf.deltaDistX = sqrt(1 + (stuff->wolf.rayDirY * \
			stuff->wolf.rayDirY) / (stuff->wolf.rayDirX * stuff->wolf.rayDirX));
		stuff->wolf.deltaDistY = sqrt(1 + (stuff->wolf.rayDirX * \
			stuff->wolf.rayDirX) / (stuff->wolf.rayDirY * stuff->wolf.rayDirY));
		setdir(stuff);
		dda(stuff);
		distance_calcultor(stuff);
		aff(stuff);
	}
	mlx_put_image_to_window(stuff->img.mlx_ptr, stuff->img.win_ptr, \
		stuff->img.img_ptr, 0, 0);
	fps_counter(stuff);
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
	stuff->wolf.hit = 0;
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
		if (stuff->map.array[stuff->wolf.mapX][stuff->wolf.mapY] > 0)
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
	stuff->draw.lineHeight = (LENGTH / stuff->draw.perpWallDist);
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
		mlx_pixel_put_to_image(stuff->img, stuff->map.x, i, 0x547681);
	while (++j < stuff->draw.end)
	{
		if (stuff->wolf.side == 0 && stuff->wolf.stepX == 1)
			mlx_pixel_put_to_image(stuff->img, stuff->map.x, j, 0x5b2C6f);
		else if (stuff->wolf.side == 0 && stuff->wolf.stepX == -1)
			mlx_pixel_put_to_image(stuff->img, stuff->map.x, j, 0x6c3483);
		else if (stuff->wolf.side == 1 && stuff->wolf.stepY == 1)
			mlx_pixel_put_to_image(stuff->img, stuff->map.x, j, 0x512e5f);
		else if (stuff->wolf.side == 1 && stuff->wolf.stepY == -1)
			mlx_pixel_put_to_image(stuff->img, stuff->map.x, j, 0x8e44ad);
	}
	j = stuff->draw.end - 1;
	while (++j < LENGTH)
		mlx_pixel_put_to_image(stuff->img, stuff->map.x, j, 0x34495e);
}
