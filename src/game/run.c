#include "game.h"
#include "render.h"

uint8_t	ft_run(t_map *map);

uint8_t	ft_run(t_map *map)
{
	t_game	s_game;
	t_graphx	s_graphx;

	ft_init_game_data(&s_game, &s_graphx, map);
	if (ft_throw_mlx_exception(ft_init_graphx(&s_game, &s_graphx)))
	{
		ft_destroy_map(s_game.map);
		return (1);
	}

	/* to remove (just for testing)*/
	int			units1;
	int			units2;
	const char	*f1 = "./maps/textures/north_texture_xpm.xpm";
	const char	*f2 = "./maps/textures/south_texture_xpm.xpm";
	const char	*f3 = "./maps/textures/west_texture_xpm.xpm";
	const char	*f4 = "./maps/textures/east_texture_xpm.xpm";

	s_game.map->texture[WALL].image[NORTH].mlx_img = mlx_xpm_file_to_image(s_game.graphx->mlx_ptr, (char *)f1, &units1, &units2);
	s_game.map->texture[WALL].image[SOUTH].mlx_img = mlx_xpm_file_to_image(s_game.graphx->mlx_ptr, (char *)f2, &units1, &units2);
	s_game.map->texture[WALL].image[WEST].mlx_img = mlx_xpm_file_to_image(s_game.graphx->mlx_ptr, (char *)f3, &units1, &units2);
	s_game.map->texture[WALL].image[EAST].mlx_img = mlx_xpm_file_to_image(s_game.graphx->mlx_ptr, (char *)f4, &units1, &units2);
	t_image		*i1 = &s_game.map->texture[WALL].image[NORTH];
	t_image		*i2 = &s_game.map->texture[WALL].image[SOUTH];
	t_image		*i3 = &s_game.map->texture[WALL].image[WEST];
	t_image		*i4 = &s_game.map->texture[WALL].image[EAST];
	i1->data = mlx_get_data_addr(i1->mlx_img, &i1->bits_per_pixel, &i1->size_line, &i1->endian);
	i2->data = mlx_get_data_addr(i2->mlx_img, &i2->bits_per_pixel, &i2->size_line, &i2->endian);
	i3->data = mlx_get_data_addr(i3->mlx_img, &i3->bits_per_pixel, &i3->size_line, &i3->endian);
	i4->data = mlx_get_data_addr(i4->mlx_img, &i4->bits_per_pixel, &i4->size_line, &i4->endian);
	s_game.map->texture[FLOOR].rgb[0] = 0xffecbf;
	s_game.map->texture[CEILING].rgb[0] = 0x43629d;
	/* to remove */

	mlx_loop_hook(s_graphx.mlx_ptr, &ft_render, &s_game);
	mlx_loop(s_graphx.mlx_ptr);
	return (0);
}
