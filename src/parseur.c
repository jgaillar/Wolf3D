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

static void		checkmap(char **str, t_stuff *stuff)
{
	int i;
	int j;

	i = -1;
	while (++i < stuff->map.maxy)
	{
		j = -1;
		while (++j < stuff->map.maxx)
		{
			if ((str[i][j] > '9' || str[i][j] < '0') && str[i][j] != ' ')
				ft_exit(-1);
		}
	}
}

size_t			linelength(char *buf)
{
	int i;
	size_t len;

	i = -1;
	len = 0;
	while (buf[++i] != '\n')
	{
		if (buf[i] != ' ')
			len++;
	}
	return (len);
}

size_t			lentab(char *buf)
{
	int		i;
	size_t	len;

	i = 0;
	len = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			len++;
		i++;
	}
	if (buf[i] == '\0' && buf[i - 1] != '\n')
		len++;
	return (len);
}

void		putintab(t_stuff *stuff)
{
	int		i;
	int		j;
	char	**tmp;
	char	**tmp2;

	ALIAS(stuff->map.array, array);
	if (!array)
		exit(0);
	i = -1;
	tmp = ft_strsplit(stuff->buf, '\n');
	checkmap(tmp, stuff);
	while (++i < stuff->map.maxy)
	{
		j = -1;
		tmp2 = ft_strsplit(tmp[i], ' ');
		while (++j < stuff->map.maxx)
			array[i][j] = ft_atoi(tmp2[j]);
		free_2d(tmp2);
	}
	free_2d(tmp);
}
