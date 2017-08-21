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
	stuff->map.maxx = linelength(stuff->buf) + 2;
	stuff->map.maxy = lentab(stuff->buf) + 2;
	stuff->map.array = malloc2d(&stuff->map);
	putintab(stuff);
}

void	init_wolf(t_stuff *stuff)
{
	stuff->wolf.wallh = 64;
	stuff->wolf.playerh = stuff->wolf.wallh/2;
	stuff->wolf.posx = 100;
	stuff->wolf.posy = 100;
	stuff->wolf.fov = 60;
	stuff->wolf.angle = 90;
	stuff->wolf.dispw = ((WIDTH/2)/tan(stuff->wolf.pov/2));
	stuff->wolf.angleray = stuff->wolf.fov/WIDTH;


}
