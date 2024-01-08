#ifndef MAP_H
# define MAP_H

# include <stddef.h>
# include <stdint.h>

# define MAP_EXTENSION_ERROR	"Missing or wrong extension file"
# define MAP_OPEN_ERROR			"Failed to open the file"
# define MAP_READ_ERROR			"Failed to read the file"
# define MAP_REQUIREMENT_ERROR	"Missing or wrong requirement"
# define MAP_PATH_ERROR			"Texture path doesn't exist or is misleading"
# define MAP_RGB_ERROR			"Missing or wrong RGB value"
# define MAP_ELEMENT_ERROR		"Missing or wrong map element"
# define MAP_LEN_ERROR			44

# define REQUIREMENT_NORTH_TEXTURE	"NO"
# define REQUIREMENT_SOUTH_TEXTURE	"SO"
# define REQUIREMENT_WEST_TEXTURE	"WE"
# define REQUIREMENT_EAST_TEXTURE	"EA"
# define REQUIREMENT_FLOOR_RGB		"F"
# define REQUIREMENT_CEILING_RGB	"C"

typedef enum	e_map_exception /* add open and read exception */
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

typedef enum	e_orientation
{
	NORTH,
	SOUTH,
	WEST,
	EST,
	N_ORIENTATION
}				t_orientation;

typedef enum	e_element
{
	EMPTY,
	WALL,
}				t_element;

typedef struct	s_map
{
	t_element	*grid;
	char		texture[N_ORIENTATION][50];
	int32_t		width;
	int32_t		height;
}				t_map;

/* init and destroy */
uint8_t			ft_init_map(char *file, t_map *map);
void			ft_destroy_map(t_map *map);

/* map parsing + error handling */
uint8_t 		ft_throw_map_exception(t_map_exception e_exception);
t_map_exception	ft_parse_map(char *file);/* in progress */
uint8_t			ft_check_extension(const char *str);
uint8_t			ft_open_file(char *str, int32_t *fd);
#endif