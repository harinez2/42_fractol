NAME		= fractol
MLIBX_DIR	= minilibx-linux
GIT_URL		= https://github.com/42Paris/minilibx-linux
MLIBX_NAME	= libmlx.a
SRCS		= main.c \
				complex_op.c \
				color.c \
				libft.c \
				draw_fractal.c \
				window.c
OBJS		= $(SRCS:.c=.o)
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
CFLAGS_L	= -L./$(MLIBX_DIR) -lmlx -lXext -lX11 -lm -lbsd

all: $(NAME)

$(MLIBX_DIR):
	git clone $(GIT_URL)

$(MLIBX_DIR)/$(MLIBX_NAME): $(MLIBX_DIR)
	cd "$(PWD)/$(MLIBX_DIR)" && make --no-print-directory

$(NAME): $(MLIBX_DIR)/$(MLIBX_NAME) $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(CFLAGS_L) $(MLIBX_DIR)/$(MLIBX_NAME) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean
	rm -rf $(MLIBX_DIR)

re: fclean all

.PHONY: all clean fclean re
