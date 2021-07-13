#include "main.h"

static void	close_win(t_mandelbrot_dataset *m)
{
	mlx_destroy_image(m->mlx, m->im1);
	exit(0);
}

void	display_window(t_mandelbrot_dataset *m)
{
	m->mlx = mlx_init();
	if (!(m->mlx))
		error_exit(ERR_INIT_MLX_FAILED);
	m->win1 = mlx_new_window(m->mlx, m->w, m->h, "fractol");
	if (!(m->win1))
		error_exit(ERR_INIT_WINDOW_FAILED);
	m->im1 = mlx_new_image(m->mlx, m->w, m->h);
	if (!(m->im1))
		error_exit(ERR_INIT_IMAGE_FAILED);
	m->data1 = mlx_get_data_addr(m->im1,
			&m->bits_per_pixel, &m->line_len, &m->endian);
	draw_mandelbrot_set(m);
	mlx_key_hook(m->win1, key_win1, m);
	mlx_mouse_hook(m->win1, mouse_win1, m);
	mlx_hook(m->win1, MotionNotify, PointerMotionMask, mouse_move_effect, m);
	mlx_hook(m->win1, ClientMessage, NoEventMask, (void *)close_win, m);
	mlx_loop(m->mlx);
}
