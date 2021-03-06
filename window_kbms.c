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

int	key_win1(int key, t_mandelbrot_dataset *m)
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

int	mouse_win1(int button, int x, int y, t_mandelbrot_dataset *m)
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
		m->scroll_cnt++;
	}
	else if (button == MOUSE_SCROOL_DOWN)
	{
		m->xmin -= (float)width * (float)x / (float)m->w * 0.1;
		m->xmax += (float)width * (1.0 - (float)x / (float)m->w) * 0.1;
		m->ymin -= (float)height * (float)y / (float)m->h * 0.1;
		m->ymax += (float)height * (1.0 - (float)y / (float)m->h) * 0.1;
		m->scroll_cnt--;
	}
	draw_mandelbrot_set(m);
	return (0);
}

static double	ft_map_minusone_plusone(double x, int froma, int fromb)
{
	int		toa;
	int		tob;
	double	pos;
	double	ret;

	toa = -1;
	tob = 1;
	pos = (x - (double)froma) / ((double)fromb - (double)froma);
	ret = pos * ((double)tob - (double)toa) + (double)toa;
	return (ret);
}

int	mouse_move_effect(int x, int y, t_mandelbrot_dataset *m)
{
	double	xparam;
	double	yparam;

	xparam = ft_map_minusone_plusone(x, 0, WIN1_SX);
	yparam = ft_map_minusone_plusone(y, 0, WIN1_SY);
	m->c = cp_init(xparam, yparam);
	draw_mandelbrot_set(m);
	return (0);
}
