#include "main.h"

static int	check_inside_of_mandelbrot_set(t_complex p, t_mandelbrot_dataset *m)
{
	t_complex	z;
	t_complex	c;
	int			i;

	if (m->type == MANDELBROT_SET)
	{
		z = m->z0;
		c = cp_init(p.x, p.i);
	}
	else if (m->type == JULIA_SET)
	{
		z = cp_init(p.x, p.i);
		c = m->c;
	}
	i = 0;
	while (i < m->num_of_reprtition)
	{
		if (fabs(z.x * z.x + z.i * z.i) > DIVERGENCE_LIMIT)
		{
			return (i);
		}
		z = cp_add(cp_sqrt(z), c);
		i++;
	}
	return (-1);
}

static t_color	calc_color(int depth, t_mandelbrot_dataset *m)
{
	t_color		color;

	set_color(&color,
		m->color.r * (float)depth / (float)m->num_of_reprtition,
		m->color.g * (float)depth / (float)m->num_of_reprtition,
		m->color.b * (float)depth / (float)m->num_of_reprtition);
	color = set_rgb_inrange(color);
	return (color);
}

void	draw_mandelbrot_set(t_mandelbrot_dataset *m)
{
	int			x;
	int			y;
	t_complex	p;
	t_color		color;
	int			ret;

	m->dx = (m->xmax - m->xmin) / (double)m->w;
	m->dy = (m->ymax - m->ymin) / (double)m->h;
	y = 0;
	while (y < m->h)
	{
		x = 0;
		while (x < m->w)
		{
			p.x = m->xmin + m->dx * (double)x;
			p.i = m->ymin + m->dy * (double)y;
			set_color(&color, 0, 0, 0);
			ret = check_inside_of_mandelbrot_set(p, m);
			if (ret != -1)
				color = calc_color(ret, m);
			mlx_pixel_put(m->mlx, m->win1, x, y, ft_color(&color));
			x++;
		}
		y++;
	}
}
