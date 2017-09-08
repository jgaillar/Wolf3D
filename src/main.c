/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgaillar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 22:17:03 by jgaillar          #+#    #+#             */
/*   Updated: 2017/06/20 00:15:03 by jgaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				checkbuf(char *buf)
{
	int i;

	i = -1;
	while (buf[++i] != '\0')
	{
		if ((buf[i] > '9' || buf[i] < '0') && buf[i] != ' ' && buf[i] != '\n')
			ft_exit(-1);
	}
	i = -1;
	while (buf[++i] != '\0')
		if (buf[i] == 48)
			return(1);
	return (0);
}

void			ft_exit(int code)
{
	ft_putstr("Error happened: ");
	ft_putnbr(code);
	ft_putendl("\nExiting.");
	exit(code);
}

static void		ft_usage(void)
{
	ft_putendl("Usage: ./wolf3d <map>");
	ft_exit(0);
}

int				main(int ac, char **av)
{
	t_stuff e;
	int i = -1;
	int j;

	if (ac != 2 || !av[1])
		ft_usage();
	if ((e.fd = open(av[1], O_RDONLY)) < 0)
		ft_exit(-1);
	e.img.mlx_ptr = mlx_init();
	e.img.win_ptr = mlx_new_window(e.img.mlx_ptr, WIDTH, LENGTH,\
			"WOLF3D");
	e.buf[read(e.fd, e.buf, BUFF_SIZE)] = '\0';
	close(e.fd);
	if (checkbuf(e.buf) == 0)
		ft_exit(-1);
	init_struct(&e);
	while (++i < e.map.maxy)
	{
		j = -1;
		while (++j < e.map.maxx)
		{
			ft_putnbr(e.map.array[i][j]);
			ft_putchar(' ');
		}
		ft_putchar('\n');
	}
	wolf3d(&e);
	mlx_hook(e.img.win_ptr, 2, (1L << 0), hooks, &e);
	mlx_hook(e.img.win_ptr, 17, (1L << 17), (int(*)())cleanexit, &e);
	mlx_loop_hook(e.img.mlx_ptr, (int(*)())wolf3d, &e);
	mlx_loop(e.img.mlx_ptr);
	return (0);
}
