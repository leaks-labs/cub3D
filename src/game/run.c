#include "game.h"

uint8_t	ft_run(t_map *map);

uint8_t	ft_run(t_map *map)
{
	t_game		s_game;
	t_graphx	s_graphx;

	ft_init_game_data(&s_game, &s_graphx, map);
	if (ft_throw_mlx_exception(ft_init_graphx(&s_game, &s_graphx)))
	{
		ft_destroy_map(s_game.map);
		return (1);
	}

	/* to remove (just for testing)*/
	const char	*f1 = "./maps/textures/north_texture_xpm.xpm";
	const char	*f2 = "./maps/textures/south_texture_xpm.xpm";
	const char	*f3 = "./maps/textures/west_texture_xpm.xpm";
	const char	*f4 = "./maps/textures/east_texture_xpm.xpm";
	const char	*f5 = "./maps/textures/north_texture_xpm.xpm";
	const char	*f6 = "./maps/textures/east_texture_xpm.xpm";
	t_image		*i1 = &s_game.map->texture[WALL].image[NORTH];
	t_image		*i2 = &s_game.map->texture[WALL].image[SOUTH];
	t_image		*i3 = &s_game.map->texture[WALL].image[WEST];
	t_image		*i4 = &s_game.map->texture[WALL].image[EAST];
	t_image		*i5 = &s_game.map->texture[FLOOR].image[NORTH];
	t_image		*i6 = &s_game.map->texture[CEILING].image[NORTH];
	int			*width_f1 = &i1->width;
	int			*height_f1 = &i1->height;
	int			*width_f2 = &i2->width;
	int			*height_f2 = &i2->height;
	int			*width_f3 = &i3->width;
	int			*height_f3 = &i3->height;
	int			*width_f4 = &i4->width;
	int			*height_f4 = &i4->height;
	int			*width_f5 = &i5->width;
	int			*height_f5 = &i5->height;
	int			*width_f6 = &i6->width;
	int			*height_f6 = &i6->height;

	i1->mlx_img = mlx_xpm_file_to_image(s_game.graphx->mlx_ptr, (char *)f1, width_f1, height_f1);
	i2->mlx_img = mlx_xpm_file_to_image(s_game.graphx->mlx_ptr, (char *)f2, width_f2, height_f2);
	i3->mlx_img = mlx_xpm_file_to_image(s_game.graphx->mlx_ptr, (char *)f3, width_f3, height_f3);
	i4->mlx_img = mlx_xpm_file_to_image(s_game.graphx->mlx_ptr, (char *)f4, width_f4, height_f4);
	i5->mlx_img = mlx_xpm_file_to_image(s_game.graphx->mlx_ptr, (char *)f5, width_f5, height_f5);
	i6->mlx_img = mlx_xpm_file_to_image(s_game.graphx->mlx_ptr, (char *)f6, width_f6, height_f6);
	i1->data = mlx_get_data_addr(i1->mlx_img, &i1->bits_per_pixel, &i1->size_line, &i1->endian);
	i2->data = mlx_get_data_addr(i2->mlx_img, &i2->bits_per_pixel, &i2->size_line, &i2->endian);
	i3->data = mlx_get_data_addr(i3->mlx_img, &i3->bits_per_pixel, &i3->size_line, &i3->endian);
	i4->data = mlx_get_data_addr(i4->mlx_img, &i4->bits_per_pixel, &i4->size_line, &i4->endian);
	i5->data = mlx_get_data_addr(i5->mlx_img, &i5->bits_per_pixel, &i5->size_line, &i5->endian);
	i6->data = mlx_get_data_addr(i6->mlx_img, &i6->bits_per_pixel, &i6->size_line, &i6->endian);
	map->texture[FLOOR].rgb[0] = 0xffecbf;
	map->texture[CEILING].rgb[0] = 0x43629d;
	/* to remove */

	mlx_loop(s_graphx.mlx_ptr);
	return (0);
}
