#include "main.h"

void	error_exit(int errcode)
{
	if (errcode == ERR_INIT_MLX_FAILED)
		perror("Error: Failed to init mlx.");
	else if (errcode == ERR_INIT_WINDOW_FAILED)
		perror("Error: Failed to init window.");
	else if (errcode == ERR_INIT_IMAGE_FAILED)
		perror("Error: Failed to init image.");
	else
		perror("Error");
	exit(-1);
}
