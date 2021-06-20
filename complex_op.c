#include "main.h"

t_complex	cp_init(float x, float i)
{
	t_complex	c;

	c.x = x;
	c.i = i;
	return (c);
}

t_complex	cp_add(t_complex c1, t_complex c2)
{
	t_complex	c;

	c.x = c1.x + c2.x;
	c.i = c1.i + c2.i;
	return (c);
}

t_complex	cp_sqrt(t_complex c)
{
	t_complex	csqrt;

	csqrt.x = c.x * c.x - c.i * c.i;
	csqrt.i = c.x * c.i * 2;
	return (csqrt);
}
