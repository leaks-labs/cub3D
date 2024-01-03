#ifndef MAP_H
# define MAP_H

# include <stddef.h>
# include <stdint.h>

# define MAP_EXTENSION_ERROR	"Missing or wrong extension file"
# define MAP_REQUIREMENT_ERROR	"Missing or wrong requirement"
# define MAP_PATH_ERROR			"Texture path doesn't exist or is misleading"
# define MAP_RGB_ERROR			"Missing or wrong RGB value"
# define MAP_ELEMENT_ERROR		"Missing or wrong map element"
# define MAP_LEN_ERROR			44

typedef enum	e_map_exception /* add open and read exception */
{
	EXTENSION_ERROR,
	REQUIREMENT_ERROR,
	PATH_ERROR,
	RGB_ERROR,
	ELEMENT_ERROR,
	N_MAP_EXCEPTION,
	NO_MAP_EXCEPTION
}				t_map_exception;

typedef enum	e_orientation
{
	NORTH,
	SOUTH,
	WEST,
	EST,
	UP,
	DOWN,
	N_ORIENTATION
}				t_orientation;

typedef enum e_element
{
	EMPTY,
	WALL
}			t_element;

typedef struct	s_texture
{
	char	*texture_path; //dllist
	uint8_t	rgb[3];
}				t_texture;

typedef struct	s_grid
{
	t_texture		texture;
	t_element		type;
	t_orientation	orientation;
	//pos
}				t_grid;

typedef struct	s_map
{
	t_grid			*grid_not_use;
	size_t			n_grid;
	int32_t			*grid;
	t_orientation	orientation;
}				t_map;

uint8_t			ft_init_map(char *file, t_map *map);
void			ft_destroy_map(t_map *map);

/* exception maybe */
uint8_t 		ft_throw_map_exception(t_map_exception e_exception);
t_map_exception	ft_parse_map(char *file);/* in progress */
uint8_t			ft_check_extension(char *file);
#endif