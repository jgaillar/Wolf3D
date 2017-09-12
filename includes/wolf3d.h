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
# define WIDTH 720
# define LENGTH 480
# define BUFF_SIZE 0xfffff
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <mlx.h>
# include <pthread.h>
# include <math.h>
# include <sys/time.h>
# include <stdio.h>
# include <../libft/libft.h>

# define ALIAS(var, name) typeof(var) name = var

typedef struct		s_wolf
{
	float			posx;
	float			posy;
	float			dirx;
	float			diry;
	float			planex;
	float			planey;
	float			time;
	float			oldtime;
	float			frametime;
	float			camerax;
	float			rayposx;
	float			rayposy;
	float			raydirx;
	float			raydiry;
	int				mapx;
	int				mapy;
	float			sidedistx;
	float			sidedisty;
	float			deltadistx;
	float			deltadisty;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	float			movespeed;
	float			rotspeed;
}					t_wolf;

typedef struct		s_draw
{
	float			perpwalldist;
	int				lineheight;
	int				start;
	int				end;
}					t_draw;

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
	char			*data;
}					t_img;

typedef	struct		s_stuff
{
	t_img			img;
	t_map			map;
	t_wolf			wolf;
	t_draw			draw;
	int				fd;
	char			buf[BUFF_SIZE + 1];
	int				i;
	int				len;
	int				big;
	int				check;
}					t_stuff;

typedef	struct		s_tmp
{
	t_stuff			*e;
	int				start;
	int				end;
}					t_tmp;

void				ft_stuffxit(int code);
int					**malloc2d(t_map *map);
void				free_2d(int **array, t_stuff *e);
void				free_2dc(char **array);
size_t				lentab(t_stuff *e);
size_t				linelength(char *buf);
void				putintab(t_stuff *e);
void				init_struct(t_stuff *e);
void				init_wolf(t_stuff *e);
void				setborders(t_stuff *e);
void				wolf3d(t_stuff *e);
void				draw_wolf(t_stuff *e);
void				setdir(t_stuff *e);
void				dda(t_stuff *e);
void				distance_calcultor(t_stuff *e);
void				aff(t_stuff *e);
void				create_image(t_stuff *e);
void				mlx_pixel_put_to_image(t_img img, int x, int y, int color);
int					hooks(int keycode, t_stuff *e);
void				echap(int keycode, t_stuff *e);
void				movement(int keycode, t_stuff *e);
void				right(int keycode, t_stuff *e);
void				left(int keycode, t_stuff *e);
void				cleanexit(t_stuff *e);
void				fps_counter(t_stuff *e);
int					check(t_stuff *e);
int					checkbuf(char *buf, t_stuff *e);
void				ft_exit(int code, t_stuff *e);
size_t				searchbigline(t_stuff *e);

#endif
