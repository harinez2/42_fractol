#include "main.h"

static void	key_UDLR(int key, t_mandelbrot_dataset *m)
{
	float	diff;

	diff = (m->xmax - m->xmin) * KEY_MOVEDIFF;
	if (key == KEY_UP)
	{
		m->ymax -= diff;
		m->ymin -= diff;
	}
	else if (key == KEY_DOWN)
	{
		m->ymax += diff;
		m->ymin += diff;
	}
	else if (key == KEY_LEFT)
	{
		m->xmax -= diff;
		m->xmin -= diff;
	}
	else if (key == KEY_RIGHT)
	{
		m->xmax += diff;
		m->xmin += diff;
	}
}

static int	key_win1(int key, t_mandelbrot_dataset *m)
{
	int		c;

	if (key == KEY_ESC)
		exit(0);
	else if (key == KEY_UP || key == KEY_DOWN
		 || key == KEY_LEFT || key == KEY_RIGHT)
		key_UDLR(key, m);
	else if (key == KEY_C)
	{
		c = m->color.r;
		m->color.r = m->color.g;
		m->color.g = m->color.b;
		m->color.b = c;
	}
	else
		return (0);
	draw_mandelbrot_set(m);
	return (0);
}

static int	mouse_win1(int button, int x, int y, t_mandelbrot_dataset *m)
{
	float	width;
	float	height;

	width = m->xmax - m->xmin;
	height = m->ymax - m->ymin;
	if (button == MOUSE_SCROOL_UP)
	{
		m->xmin += (float)width * (float)x / (float)m->w * 0.1;
		m->xmax -= (float)width * (1.0 - (float)x / (float)m->w) * 0.1;
		m->ymin += (float)height * (float)y / (float)m->h * 0.1;
		m->ymax -= (float)height * (1.0 - (float)y / (float)m->h) * 0.1;
	}
	else if (button == MOUSE_SCROOL_DOWN)
	{
		m->xmin -= (float)width * (float)x / (float)m->w * 0.1;
		m->xmax += (float)width * (1.0 - (float)x / (float)m->w) * 0.1;
		m->ymin -= (float)height * (float)y / (float)m->h * 0.1;
		m->ymax += (float)height * (1.0 - (float)y / (float)m->h) * 0.1;
	}
	draw_mandelbrot_set(m);
	return (0);
}

static void	close_win(void)
{
	exit(0);
}

void	display_window(t_mandelbrot_dataset *m)
{
	m->mlx = mlx_init();
	if (!(m->mlx))
	{
		ft_putchars("Error: Failed to init mlx.\n");
		exit(-1);
	}
	m->win1 = mlx_new_window(m->mlx, m->w, m->h, "fractol");
	if (!(m->win1))
	{
		ft_putchars("Error: Failed to init window.\n");
		exit(-1);
	}
	draw_mandelbrot_set(m);
	mlx_key_hook(m->win1, key_win1, m);
	mlx_mouse_hook(m->win1, mouse_win1, m);
	mlx_hook(m->win1, 33, 0, (void *)close_win, 0);
	mlx_loop(m->mlx);
}
