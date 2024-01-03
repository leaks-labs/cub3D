#ifndef MAP_H
# define MAP_H

# include <stddef.h>
# include <stdint.h>

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

uint8_t	ft_set_map(int argc, char **argv, t_map *map);

void	ft_destroy_map(t_map *map);

#endif