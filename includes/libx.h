#ifndef LIBX_H
# define LIBX_H

# include <stddef.h>
# include <stdint.h>
# include "mlx.h"

# define WINDOW_NAME		"cub3d"
# define WINDOW_WIDTH		500
# define WINDOW_HEIGHT		500

# define MLX_INIT_ERROR		"Failed to initialise mlx"
# define MLX_WINDOW_ERROR	"Failed to initialise the window"
# define MLX_IMAGE_ERROR	"Failed to initialise image"
# define MLX_LEN_ERROR		32

typedef struct s_pixel		t_pixel;
typedef struct s_game_data	t_game_data;

# ifdef __linux__

typedef enum e_keyboard
{
	KEY_ESC = 65307,
	KEY_W = 119,
	KEY_S = 115,
	KEY_D = 100,
	KEY_A = 97,
	KEY_ARROW_LEFT = 65361,
	KEY_ARROW_RIGHT = 65363,
	N_KEY = 7
}			t_keyboard;

# elif __APPLE__

typedef enum e_keyboard
{
	KEY_ESC = 53,
	KEY_W = 13,
	KEY_S = 1,
	KEY_D = 2,
	KEY_A = 0,
	KEY_ARROW_LEFT = 123,
	KEY_ARROW_RIGHT = 124,
	N_KEY = 7
}			t_keyboard;

# endif

typedef enum e_mlx_exception
{
	INIT_ERROR,
	CREATE_WINDOW_ERROR,
	CREATE_IMAGE_ERROR,
	N_EXCEPTION,
	NO_EXCEPTION
}				t_mlx_exception;

typedef struct s_image
{
	void	*mlx_img;
	char	*data;
	int32_t	bits_per_pixel;
	int32_t	size_line;
	int32_t	endian;
}				t_image;

typedef struct s_window
{
	void		*mlx_win;
	t_image		image; /* could be an array of 2 if minimap or a ptr */
}				t_window;

typedef struct s_graphx
{
	void		*mlx_ptr;
	t_window	window; /* could be a ptr, but struct is fine for the project */
}				t_graphx;

/* init and destroy */
t_mlx_exception	ft_init_graphx(t_game_data *game_data, t_graphx *graphx);
void			ft_destroy_graphx(t_graphx *graphx);

/* handlers */
int32_t			ft_key_handler(int32_t key_code, t_game_data *game_data);
/* Maybe add mousse handler */

/* error handling */
uint8_t			ft_throw_mlx_exception(t_mlx_exception e_exception);

/* print to screen */
void			ft_refresh(t_game_data *gd);
void			ft_pixel_put(t_image *img, t_pixel *coord);
void			ft_pixel_cpy(t_image *img_src, t_image *img_dst, \
						t_pixel *src, t_pixel *dst);

#endif
