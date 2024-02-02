/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libx.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leex-Labs <leakslabs@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:22:47 by Leex-Labs         #+#    #+#             */
/*   Updated: 2024/02/02 01:22:48 by Leex-Labs        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBX_H
# define LIBX_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include "mlx.h"

# define WINDOW_NAME			"cub3d"
# define WINDOW_WIDTH			1280
# define WINDOW_HEIGHT			720
# define MINI_MAP_WIDTH			300
# define MINI_MAP_HEIGHT		300
# define MINI_MAP_PIX_PER_CELL	30

# define MLX_INIT_ERROR		"Failed to initialise mlx"
# define MLX_WINDOW_ERROR	"Failed to initialise the window"
# define MLX_IMAGE_ERROR	"Failed to initialise image"
# define MLX_LEN_ERROR		32

# define ON_KEYDOWN			2
# define ON_KEYUP			3
# define ON_MOUSEMOVE		6
# define ON_DESTROY			17

typedef struct s_pixel		t_pixel;
typedef struct s_game		t_game;
typedef struct s_texture	t_texture;
typedef enum e_element		t_element;
typedef enum e_orientation	t_orientation;

# ifdef __linux__

typedef enum e_keyboard
{
	KEY_W = 119,
	KEY_S = 115,
	KEY_D = 100,
	KEY_A = 97,
	KEY_ARROW_LEFT = 65361,
	KEY_ARROW_RIGHT = 65363,
	KEY_ARROW_DOWN = 65364,
	KEY_ARROW_UP = 65362,
	KEY_I = 105,
	KEY_O = 111,
	KEY_M = 109,
	KEY_P = 112,
	KEY_ESC = 65307,
	N_KEY = 13
}			t_keyboard;

# elif __APPLE__

typedef enum e_keyboard
{
	KEY_W = 13,
	KEY_S = 1,
	KEY_D = 2,
	KEY_A = 0,
	KEY_ARROW_LEFT = 123,
	KEY_ARROW_RIGHT = 124,
	KEY_ARROW_DOWN = 125,
	KEY_ARROW_UP = 126,
	KEY_I = 34,
	KEY_O = 31,
	KEY_M = 46,
	KEY_P = 35,
	KEY_ESC = 53,
	N_KEY = 13
}			t_keyboard;

# endif

typedef enum e_keyboard_bitwise
{
	BIT_KEY_W = 1,
	BIT_KEY_S = 2,
	BIT_KEY_D = 4,
	BIT_KEY_A = 8,
	BIT_KEY_ARROW_LEFT = 16,
	BIT_KEY_ARROW_RIGHT = 32,
	BIT_KEY_ARROW_DOWN = 64,
	BIT_KEY_ARROW_UP = 128,
	BIT_KEY_I = 256,
	BIT_KEY_O = 512,
	N_BIT_KEY = 10
}				t_keyboard_bitwise;

typedef enum e_mlx_exception
{
	INIT_ERROR,
	CREATE_WINDOW_ERROR,
	CREATE_IMAGE_ERROR,
	N_EXCEPTION,
	NO_EXCEPTION
}				t_mlx_exception;

typedef struct s_dic_keys
{
	int		keycode;
	int32_t	bitwise;
}				t_dic_keys;

typedef struct s_image
{
	void	*mlx_img;
	char	*data;
	int32_t	bits_per_pixel;
	int32_t	size_line;
	int32_t	endian;
	int		width;
	int		height;
}				t_image;

typedef struct s_window
{
	void		*mlx_win;
	t_image		s_image;
}				t_window;

typedef struct s_graphx
{
	void		*mlx_ptr;
	t_window	s_window;
}				t_graphx;

/* init and destroy */
t_mlx_exception	ft_init_graphx(t_game *game, t_graphx *graphx);
void			ft_destroy_graphx(t_game *game);
t_mlx_exception	ft_open_texture(t_texture *texture, void *mlx_ptr);
void			ft_destroy_texture(void *mlx_ptr, t_texture *texture, \
									t_orientation e_orientation, \
									t_element e_element);

/* new image */
void			*ft_mlx_new_image(void *mlx_ptr, void **mlx_img);
void			ft_mlx_get_data_addr(t_image *image);
void			*ft_mlx_new_mini_map_image(void *mlx_ptr, void **mlx_img);
void			ft_set_images_metadata(t_game *game, t_graphx *graphx);

/* key handlers */
int32_t			ft_key_down_handler(int32_t key_code, t_game *game);
int				ft_key_up_handler(int32_t key_code, t_game *game);

/* mouse handlers */
int				ft_on_destroy(t_game *game);
int				ft_on_mouse_move(int x, int y, t_game *game);

/* error handling */
uint8_t			ft_throw_mlx_exception(t_mlx_exception e_exception);

/* print to screen */
void			ft_refresh(t_game *game);
void			ft_refresh_mini_map(t_game *game);
void			ft_pixel_put(t_image *img, t_pixel *coord);
void			ft_pixel_cpy(t_image *img_src, t_image *img_dst, \
								t_pixel *src, t_pixel *dst);

#endif
