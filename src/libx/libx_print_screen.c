#include "libx.h"
#include "game.h"
#include "utils.h"

void	ft_refresh(t_game_data *gd);
void	ft_pixel_put(t_image *img, t_pixel *coord);
void	ft_pixel_cpy(t_image *img_src, t_image *img_dst, \
						t_pixel *src, t_pixel *dst);

void	ft_refresh(t_game_data *gd)
{
	mlx_put_image_to_window(gd->graphx->mlx_ptr, gd->graphx->window.mlx_win, \
							gd->graphx->window.image.mlx_img, 0, 0);
}

void	ft_pixel_put(t_image *img, t_pixel *coord)
{
	char	*pixel;
	int		i;

	if (coord->x < 0 || coord->x >= WINDOW_WIDTH \
			|| coord->y < 0 || coord->y >= WINDOW_HEIGHT)
		return ;
	i = img->bits_per_pixel - 8;
	pixel = img->data + \
			(coord->y * img->size_line + coord->x * (img->bits_per_pixel / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (char)((coord->colour >> i) & 0xFF);
		else
			*pixel++ = (char)((coord->colour >> (img->bits_per_pixel - 8 - i)) \
								& 0xFF);
		i -= 8;
	}
}

void	ft_pixel_cpy(t_image *img_src, t_image *img_dst, \
						t_pixel *src, t_pixel *dst)
{
	char	*pixel_src;
	char	*pixel_dst;

	pixel_src = img_src->data + (src->y * img_src->size_line + src->x \
								* (img_src->bits_per_pixel >> 3));
	pixel_dst = img_dst->data + (dst->y * img_dst->size_line + dst->x \
								* (img_dst->bits_per_pixel >> 3));
	ft_memcpy(pixel_dst, pixel_src, (size_t)(img_dst->bits_per_pixel >> 3));
}
