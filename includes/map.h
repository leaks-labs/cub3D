#ifndef MAP_H
# define MAP_H

# include "libx.h"

# define MAP_EXTENSION_ERROR	"Missing or wrong extension file"
# define MAP_OPEN_ERROR			"Failed to open the file"
# define MAP_READ_ERROR			"Failed to read the file"
# define MAP_REQUIREMENT_ERROR	"Missing or wrong requirement"
# define MAP_PATH_ERROR			"Texture path doesn't exist or is misleading"
# define MAP_RGB_ERROR			"Missing or wrong RGB value"
# define MAP_ELEMENT_ERROR		"Missing or wrong map element"

# define MAP_LEN_ERROR				44
# define REQUIREMENT_NORTH_TEXTURE	"NO"
# define REQUIREMENT_SOUTH_TEXTURE	"SO"
# define REQUIREMENT_WEST_TEXTURE	"WE"
# define REQUIREMENT_EAST_TEXTURE	"EA"
# define REQUIREMENT_FLOOR_RGB		"F"

# define REQUIREMENT_CEILING_RGB	"C"

typedef enum e_map_exception
{
	EXTENSION_ERROR,
	OPEN_ERROR,
	READ_ERROR,
	REQUIREMENT_ERROR,
	PATH_ERROR,
	RGB_ERROR,
	ELEMENT_ERROR,
	N_MAP_EXCEPTION,
	NO_MAP_EXCEPTION
}				t_map_exception;

typedef enum e_orientation
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	N_ORIENTATION
}			t_orientation;

typedef enum e_element
{
	EMPTY,
	WALL,
	FLOOR,
	CEILING,
	N_ELEMENT
}				t_element;

typedef struct s_texture
{
	char	orientation[N_ORIENTATION][50]; /* PATH MAX */
	t_image	image[N_ORIENTATION];
	int32_t	rgb[N_ORIENTATION];
}				t_texture;

typedef struct s_vec
{
	double	x;
	double	y;
}				t_vec;

typedef struct s_player
{
	t_vec			s_pos;
	t_vec			s_dir;
	t_vec			s_plane;
	t_orientation	e_orientation;
}				t_player;

typedef struct s_mini_map
{
	t_image	s_image;
	int		wall_color;
	int		empty_color;
	int		units;
	double	steps;
	double	angle;
}				t_mini_map;

typedef struct s_map
{
	t_element	*grid;
	t_texture	texture[N_ELEMENT];
	int32_t		width;
	int32_t		height;
	t_player	s_player;
	t_mini_map	s_mini_map;
}				t_map;

/* init and destroy */
uint8_t			ft_init_map(char *file, t_map *map);
void			ft_destroy_map(t_map *map);

/* map parsing + error handling */
uint8_t			ft_throw_map_exception(t_map_exception e_exception);
t_map_exception	ft_parse_map(char *file);/* in progress */

#endif
