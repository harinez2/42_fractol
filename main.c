#include "main.h"

#include <stdio.h>

static void	init_mandelbrot_dataset(t_mandelbrot_dataset *m)
{
	m->w = WIN1_SX;
	m->h = WIN1_SY;
	m->xmin = -2.0;
	m->xmax = 2.0;
	m->ymin = -2.0;
	m->ymax = 2.0;
	m->dyndraw = 0;
	m->type = NOT_SET;
	m->num_of_reprtition = 25;
	m->scroll_cnt = 0;
	m->color.r = 255;
	m->color.g = 0;
	m->color.b = 255;
}

static void	print_usage_exit(void)
{
	ft_putchars("usage: ./fractol OPTIONS [PARAMETERS...]\n");
	ft_putchars("\n");
	ft_putchars("Options:\n");
	ft_putchars("    -m               Draw mandelbrot sets.\n");
	ft_putchars("    -j               Draw julia sets.\n");
	ft_putchars("Parameters:\n");
	ft_putchars("    --rep="TX_UNDERLINE"TIMES"TX_DEFAULT_DECO);
	ft_putchars("      The number of repetition to calculate.\n");
	ft_putchars("    --color="TX_UNDERLINE"COLOR"TX_DEFAULT_DECO);
	ft_putchars("    Color. Specify rgb range in hexadecimal.\n");
	ft_putchars("                       ");
	ft_putchars("ex) --color=FF00FF represents purple.\n");
	ft_putchars("Parameters (only for julia set):\n");
	ft_putchars("    --c="TX_UNDERLINE"X:Y"TX_DEFAULT_DECO);
	ft_putchars("          Initial value of C.\n");
	ft_putchars("    --dd             ");
	ft_putchars("Change the initial parameters based on the mouse position.\n");
	ft_putchars("Tips:\n");
	ft_putchars("  - Press ESC or x button on the window to exit.\n");
	ft_putchars("  - Press C to shift the color range.\n");
	ft_putchars("  - You can use mouse wheel to expand/shrink the object.\n");
	ft_putchars("\n");
	exit (0);
}

static void	read_parameters_float(char *param, t_mandelbrot_dataset *m)
{
	float	readfx;
	float	readfy;
	int		j;
	int		ret;

	readfx = 0;
	readfy = 0;
	if (ft_strncmp(param, "--c=", 4) == 0)
	{
		j = 4;
		ret = ft_ftoi(&param[j], &readfx);
		if (ret != 0)
		{
			j += ret + 1;
			ret = ft_ftoi(&param[j], &readfy);
			if (ret != 0)
			{
				m->c = cp_init(readfx, readfy);
			}
		}
	}
}

static void	read_parameters(char *param, t_mandelbrot_dataset *m)
{
	int		readi;
	int		j;

	readi = 0;
	if (ft_strncmp(param, "--dd", 5) == 0)
		m->dyndraw = 1;
	else if (ft_strncmp(param, "--rep=", 6) == 0)
	{
		j = 6;
		while (param[j] >= '0' && param[j] <= '9')
			readi = readi * 10 + param[j++] - '0';
		if (param[j] == '\0')
			m->num_of_reprtition = readi;
	}
	else if (ft_strncmp(param, "--color=", 8) == 0)
	{
		j = 8;
		if (ft_hextoi(&param[j], &readi) != 0)
		{
			m->color.r = readi >> 16;
			m->color.g = readi >> 8 & 0xFF;
			m->color.b = readi & 0xFF;
		}
	}
	read_parameters_float(param, m);
}

int	main(int argc, char **argv)
{
	int						i;
	t_mandelbrot_dataset	m;

	init_mandelbrot_dataset(&m);
	i = 1;
	while (i < argc)
	{
		if (ft_strncmp(argv[i], "-m", 3) == 0)
		{
			m.type = MANDELBROT_SET;
			m.z0 = cp_init(0.0, 0.0);
		}
		else if (ft_strncmp(argv[i], "-j", 3) == 0)
		{
			m.type = JULIA_SET;
			m.c = cp_init(-0.04, 0.695);
		}
		else
			read_parameters(argv[i], &m);
		i++;
	}
	if (m.type == NOT_SET)
		print_usage_exit();
	display_window(&m);
	return (0);
}
