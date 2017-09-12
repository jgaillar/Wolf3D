/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgaillar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 13:28:34 by jgaillar          #+#    #+#             */
/*   Updated: 2017/08/22 10:48:40 by jgaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		**malloc2d(t_map *map)
{
	int		**array;
	int		i;

	i = -1;
	if (!(array = (int **)malloc(sizeof(int *) * (map->maxy))))
		exit(0);
	while (++i < map->maxy)
		if (!(array[i] = (int *)malloc(sizeof(int) * (map->maxx))))
			exit(0);
	return (array);
}

void	free_2d(int **array, t_stuff *e)
{
	free(array);
	array = NULL;
}

void	free_2dc(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
	   ft_strdel(&array[i]);
	free(array);
	array = NULL;
}
