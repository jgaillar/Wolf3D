/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgaillar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 22:10:07 by jgaillar          #+#    #+#             */
/*   Updated: 2017/08/07 11:13:07 by jgaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H

# define WOLF3D_H
# define WIDTH 800
# define LENGTH 800
# define BUFF_SIZE 0xfffff
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <mlx.h>
# include <pthread.h>
# include <math.h>
# include <../libft/libft.h>

# define MT 16
# define ALIAS(var, name) typeof(var) name = var

typedef struct		s_map
{
	size_t			x;
	size_t			y;
	size_t			maxx;
	size_t			maxy;
	int				**array;
}					t_map;

typedef struct		s_img
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				size;
	int				color[51];
	char			*data;
}					t_img;

typedef	struct		s_stuff
{
	t_img			img;
	t_map			map;
	pthread_t		*th;
	int				fd;
	char			buf[BUFF_SIZE + 1];
}					t_stuff;

typedef	struct		s_tmp
{
	t_stuff			*stuff;
	double			start;
	double			end;
}					t_tmp;

void				ft_exit(int code);
int					**malloc2d(t_map *map);
void				free_2d(char **array);
size_t				lentab(char *buf);
size_t				linelength(char *buf);
void				putintab(t_stuff *stuff);
void				init_struct(t_stuff *stuff);

#endif
