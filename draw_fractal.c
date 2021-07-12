#include "main.h"

static void	init_formula(t_mandelbrot_dataset *m, t_complex p,
		t_complex *z, t_complex *c)
{
	if (m->type == MANDELBROT_SET)
	{
		*z = m->z0;
		*c = cp_init(p.x, p.i);
	}
	else if (m->type == JULIA_SET)
	{
		*z = cp_init(p.x, p.i);
		*c = m->c;
	}
}

static int	check_inside_of_mandelbrot_set(t_complex p, t_mandelbrot_dataset *m)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			rep_cnt;

	init_formula(m, p, &z, &c);
	i = 0;
	rep_cnt = m->num_of_reprtition;
	if (m->scroll_cnt > 0)
		rep_cnt += m->scroll_cnt * SCROLL_CALC_DIFF;
	while (i < rep_cnt)
	{
		if (fabs(z.x * z.x + z.i * z.i) > DIVERGENCE_LIMIT)
			return (i);
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

static void	pixel_put_on_buff(t_mandelbrot_dataset *m, int x, int y, int color)
{
	char	*dst;

	dst = m->data1 + (y * m->line_len + x * (m->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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
	y = -1;
	while (++y < m->h)
	{
		x = -1;
		while (++x < m->w)
		{
			p.x = m->xmin + m->dx * (double)x;
			p.i = m->ymin + m->dy * (double)y;
			set_color(&color, 0, 0, 0);
			ret = check_inside_of_mandelbrot_set(p, m);
			if (ret != -1)
				color = calc_color(ret, m);
			pixel_put_on_buff(m, x, y, ft_color(&color));
		}
	}
	mlx_put_image_to_window(m->mlx, m->win1, m->im1, 0, 0);
}
