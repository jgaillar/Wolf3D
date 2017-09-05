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
