/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgaillar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:53:21 by jgaillar          #+#    #+#             */
/*   Updated: 2017/06/15 22:38:49 by jgaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

size_t			searchbigline(t_stuff *e, char *buf)
{
	e->i = -1;
	e->len = 0;
	e->big = 0;
	e->check = 0;
	while (buf[++e->i])
	{
		if (buf[e->i] != ' ' && buf[e->i] != '\n')
		{
			e->len++;
			while (buf[e->i] != ' ' && buf[e->i] != '\n')
				++e->i;
		}
		if (buf[e->i] == '\n')
		{
			e->check++;
			if ((e->big < e->len || e->big > e->len) && e->check > 1)
				ft_exit(-1);
			e->big = e->len;
			e->len = 0;
		}
	}
	return (e->big >= e->len ? e->big : e->len);
}

size_t			lentab(char *buf)
{
	int		i;
	size_t	len;

	i = -1;
	len = 0;
	while (buf[++i])
	{
		if (buf[i] == '\n')
			len++;
	}
	if (buf[i] == '\0' && buf[i - 1] != '\n')
		len++;
	return (len);
}

void			putintab(t_stuff *e)
{
	int		i;
	int		j;
	char	**tmp;
	char	**tmp2;

	ALIAS(e->map.array, array);
	if (!array)
		exit(0);
	i = 0;
	tmp = ft_strsplit(e->buf, '\n');
	while (++i < e->map.maxy - 1)
	{
		j = 0;
		tmp2 = ft_strsplit(tmp[i - 1], ' ');
		while (++j < e->map.maxx - 1)
			array[i][j] = ft_atoi(tmp2[j - 1]);
		free_2d(tmp2);
	}
	free_2d(tmp);
	setborders(e);
}

void			setborders(t_stuff *e)
{
	int i;
	int j;

	i = 0;
	j = -1;
	ALIAS(e->map.array, array);
	while (++j < e->map.maxx)
		array[0][j] = 1;
	j = -1;
	while (++j < e->map.maxx)
		array[e->map.maxy - 1][j] = 1;
	while (++i < e->map.maxy - 1)
	{
		array[i][0] = 1;
		array[i][e->map.maxx - 1] = 1;
	}
}
