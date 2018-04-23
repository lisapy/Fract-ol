#include "fractol.h"

void redraw(t_map *map)
{
	mlx_clear_window(map->mlx, map->win);
	ft_bzero(map->image, WIN_H * WIN_W * 4);
	draw(map);
	show_menu(map);
	mlx_put_image_to_window(map->mlx, map->win, map->n_i, 200, 0);
}

void	set_color(t_map *map, int x, int y)
{
	int	pos;

	pos = x * 4 + y * map->s_l;
	if (pos >= 0 && pos < WIN_H * WIN_W * 4)
	{
		map->image[pos] = map->color->r;
		map->image[pos + 1] = map->color->g;
		map->image[pos + 2] = map->color->b;
	}
}

void	init_fractol(t_map *map)
{
		if (map->f->fract == 1)
        {
            map->fract = draw_mandelbrot;
            init_mandelbrot(map);
        }
		else if (map->f->fract == 2)
        {
            map->fract = ship_draw;
            init_ship(map);
        }
		else if (map->f->fract == 3)
        {
            map->fract = julia_draw;
            init_julia(map);
        }
		draw(map);
}

void	show_menu(t_map* map)
{
	mlx_string_put(map->mlx, map->win, 30, 25,  0xFFFFFF, "Fractal\n");
	mlx_string_put(map->mlx, map->win, 25, 100, 0xFFFFFF, "Iteration:");
	mlx_string_put(map->mlx, map->win, 150, 100, 0xFFFFFF, ft_itoa(map->f->iter));
	mlx_string_put(map->mlx, map->win, 40, 300,  0xFFFFFF, "Controls:\n");
	mlx_string_put(map->mlx, map->win, 25, 330, 0xFFFFFF,  "[R] - reset");
	mlx_string_put(map->mlx, map->win, 25, 360, 0xFFFFFF,  "[ARROWS] - move");
	mlx_string_put(map->mlx, map->win, 25, 390, 0xFFFFFF,  "[+/-] - iteration");
	
	if (map->f->fract == 3)
		mlx_string_put(map->mlx, map->win, 25, 420, 0xFFFFFF,  "[SPACE] - rotate");
	mlx_string_put(map->mlx, map->win, 150, 100, 0xFFFFFF, ft_itoa(map->f->iter));
	
	if (map->f->pause == 1)
		mlx_string_put(map->mlx, map->win, 25, 500, 0xFF, "PAUSE");
	else
		mlx_string_put(map->mlx, map->win, 25, 500, 0, "       ");
}