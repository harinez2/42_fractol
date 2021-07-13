#ifndef MAIN_H
# define MAIN_H

# include	"minilibx-linux/mlx.h"
# include	"minilibx-linux/mlx_int.h"
# include	<math.h>

# define	WIN1_SX		400
# define	WIN1_SY		400

# define	DIVERGENCE_LIMIT	2.0
# define	SCROLL_CALC_DIFF	6

# define	NOT_SET			0
# define	MANDELBROT_SET	1
# define	JULIA_SET		2

typedef struct s_complex
{
	float	x;
	float	i;
}	t_complex;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_mandelbrot_dataset
{
	void		*mlx;
	void		*win1;
	void		*im1;
	char		*data1;
	int			bits_per_pixel;
	int			line_len;
	int			endian;
	int			type;
	int			w;
	int			h;
	float		xmin;
	float		ymin;
	float		xmax;
	float		ymax;
	float		dx;
	float		dy;
	t_complex	c;
	t_complex	z0;
	int			num_of_reprtition;
	int			scroll_cnt;
	t_color		color;
}	t_mandelbrot_dataset;

// key map
# define KEY_ESC		0xFF1B
# define KEY_UP			0xff52
# define KEY_DOWN		0xff54
# define KEY_LEFT		0xff51
# define KEY_RIGHT		0xff53
# define KEY_C			0x63
# define KEY_MOVEDIFF	0.1

// mouse map
# define MOUSE_SCROOL_UP	4
# define MOUSE_SCROOL_DOWN	5
# define MOUSE_SCROOL_STEP	0.1

// character code
# define TX_UNDERLINE		"\x1b[4m"
# define TX_DEFAULT_DECO	"\x1b[0m"

// error code
# define ERR_INIT_MLX_FAILED	-1
# define ERR_INIT_WINDOW_FAILED	-2
# define ERR_INIT_IMAGE_FAILED	-3

t_complex	cp_init(float x, float i);
t_complex	cp_add(t_complex c1, t_complex c2);
t_complex	cp_sqrt(t_complex c);

int			ft_color(t_color *c);
void		set_color(t_color *c, double red, double green, double blue);
t_color		set_rgb_inrange(t_color c);
void		ft_colorprint(t_color *c);

size_t		ft_strlen(const char *str);
void		ft_putchars(char *s);
int			ft_strncmp(char *s1, char *s2, unsigned int n);
int			ft_ftoi(char *s, float *num);
int			ft_hextoi(char *s, int *num);

void		draw_mandelbrot_set(t_mandelbrot_dataset *m);

int			key_win1(int key, t_mandelbrot_dataset *m);
int			mouse_win1(int button, int x, int y, t_mandelbrot_dataset *m);
int			mouse_move_effect(int x, int y, t_mandelbrot_dataset *m);

void		display_window(t_mandelbrot_dataset *m);

void		error_exit(int errcode);

#endif
