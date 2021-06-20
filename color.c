#include "main.h"

int	ft_color(t_color *c)
{
	int	ret;

	ret = (c->r << 16) + (c->g << 8) + c->b;
	return (ret);
}

void	set_color(t_color *c, double red, double green, double blue)
{
	c->r = red;
	c->g = green;
	c->b = blue;
	return ;
}

t_color	set_rgb_inrange(t_color c)
{
	if (c.r > 255)
		c.r = 255;
	if (c.r < 0)
		c.r = 0;
	if (c.g > 255)
		c.g = 255;
	if (c.g < 0)
		c.g = 0;
	if (c.b > 255)
		c.b = 255;
	if (c.b < 0)
		c.b = 0;
	return (c);
}

void	ft_colorprint(t_color *c)
{
	printf("rgb: %d, %d, %d", c->r, c->g, c->b);
}
