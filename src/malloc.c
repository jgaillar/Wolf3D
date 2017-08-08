/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgaillar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 13:28:34 by jgaillar          #+#    #+#             */
/*   Updated: 2017/04/04 13:30:06 by jgaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		**malloc2d(t_map *map)
{
	int		**array;
	int		i;

	i = -1;
	if (!(array = (int **)ft_memalloc(sizeof(int *) * (map->maxy))))
		exit(0);
	while (++i < map->maxy)
		if (!(array[i] = (int *)ft_memalloc(sizeof(int) * (map->maxx))))
			exit(0);
	return (array);
}

void	free_2d(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		ft_strdel(&array[i]);
	free(array);
	array = NULL;
}
