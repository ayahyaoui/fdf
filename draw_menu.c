#include "fdf.h"


void		draw_menu_background(t_mlx *mlx)
{
	int i;
	int j;

	i = 0;
	
	while (i < mlx->size_y)
	{
		j = 0;
		while (j < mlx->size_line_menu)
		{
			mlx->draw_menu[i * mlx->size_line_menu + j] = 127;
			j++;
		}
		i++;
	}
}

int         draw_menu_zoom(t_fdf *fdf, t_mlx *mlx, int y)
{
    mlx_string_put(mlx->mlx_ptr, mlx->win, mlx->width_menu / 5, y, set_b(0, 255), "ZOOM");
    return y;
}

int        draw_menu_projection(t_fdf *fdf, t_mlx *mlx, int y)
{
        printf("%d\n", fdf->type_projection);
        mlx_string_put(mlx->mlx_ptr, mlx->win, mlx->width_menu / 5, y, set_b(0, 255), "PROJECTION");
        y += 30;
        mlx_string_put(mlx->mlx_ptr, mlx->win, mlx->width_menu / 4, y, 
        fdf->type_projection == D2 ? set_g(0, 255) : set_r(0, 255), "ORTHO");
        y += 30;
        mlx_string_put(mlx->mlx_ptr, mlx->win, mlx->width_menu / 4, y,
        fdf->type_projection == ISOMETRIC ? set_g(0, 255) : set_r(0, 255) , "ISOMETRIC");
        y += 30;
        mlx_string_put(mlx->mlx_ptr, mlx->win, mlx->width_menu / 4, y,
        fdf->type_projection == PARALLELE ? set_g(0, 255) : set_r(0, 255) , "PARALLELE");
        return y;
}

void        draw_menu(t_fdf *fdf)
{   
    int     init_y;
    t_mlx   *mlx;

    mlx = fdf->mlx;
    init_y = 150;
    draw_menu_background(fdf->mlx); // also clear img
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img_menu, 0, 0);
    init_y = draw_menu_projection(fdf, fdf->mlx, init_y);
    init_y += 100;
    init_y = draw_menu_zoom(fdf, fdf->mlx, init_y);
    init_y += 100;
    
}