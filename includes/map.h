#ifndef MAP_H
# define MAP_H

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

typedef struct	s_texture
{
	char	*texture_path; //dllist
	uint8_t	rgb[3];
}				t_texture;

typedef struct	s_grid
{
	t_texture texture[N_ORIENTATION];
	//element
}				t_grid;

typedef struct	s_map
{
	int16_t 		width;
	int16_t 		height;
	t_grid			*notUse;
	int32_t 	 		*grid;
	t_orientation	orientation;
}				t_map;

uint8_t	ft_set_map(int argc, char *argv[], t_map *map);

void	ft_destroy_map(t_map *map);

#endif