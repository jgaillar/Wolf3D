/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgaillar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 14:14:47 by jgaillar          #+#    #+#             */
/*   Updated: 2017/09/07 14:14:48 by jgaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		hooks(int keycode, t_stuff *stuff)
{
	echap(keycode, stuff);
	movement(keycode, stuff);
	right(keycode, stuff);
	left(keycode, stuff);
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
