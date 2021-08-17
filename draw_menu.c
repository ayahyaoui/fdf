#include "fdf.h"

#define PLUS_BUTTON_NAME "plusbutton.xpm" // A CHANGER
#define MINUS_BUTTON_NAME "minusbutton.xpm"

/*
        gray background
*/
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

void		put_point_menu_color(t_mlx *mlx, int x, int y, int color)
{
	if (y >= 0 && y < mlx->size_y && x >= 0 && x < mlx->width_menu)
	{
		mlx->draw_menu[y * mlx->size_line_menu + x * 4 ] = (color) % 256;
		mlx->draw_menu[y * mlx->size_line_menu + x * 4 + 1] = (color >> 8) % 256;
		mlx->draw_menu[y * mlx->size_line_menu + x * 4 + 2] = (color >> 16) % 256;
		mlx->draw_menu[y * mlx->size_line_menu + x * 4+ 3] = (color >> 24) % 256;
	}
}

void		draw_graduation(t_fdf *fdf, t_mlx *mlx, int pos_y, int lim_y, t_option option)
{
    int start_x;
    int j;
    double proportion;


    proportion = get_proportion(fdf, option);
    start_x = (int)((double)(BUTTON_LEFT_W + mlx->width_menu / 20) * 4);
	while (pos_y < lim_y)
	{
		j = 0;
        while (j < ((mlx->width_menu * 8 / 3) - start_x) * proportion)
        {
            put_point_menu_color(mlx, (start_x + j) / 4, pos_y, set_g(0, 255));  
            j+= 4;
        }
		while(j < (mlx->width_menu * 8 / 3) - start_x )
        {
             put_point_menu_color(mlx, (start_x + j) / 4, pos_y, GRADUATION_BACKGROUND_COLOR);
            j += 4;
        }
		pos_y++;
	}
}

void		draw_menu_graduation(t_fdf *fdf, t_mlx *mlx, const t_menu *type, const t_option options[])
{
    int index;
    int graduation_index;
    int add_pos;
    
    graduation_index = 0;
    add_pos = (!fdf->button_grad_y) ? 1 : 0;
	if (add_pos)
        fdf->button_grad_y = ft_memalloc(sizeof(int) * GRADUATION_SIZE);
    index = -1;
    while (++index < GRID_NB)
    {
        if (type[index] == GRADUATION)
        {
            if (add_pos)
                fdf->button_grad_y[graduation_index++] = index * mlx->size_y / GRID_SIZE;
            draw_graduation( fdf, mlx, index * mlx->size_y / GRID_SIZE, (index + 1) * mlx->size_y / GRID_SIZE, options[index]);
            index++;
        }
    }
}

int         put_graduation(t_fdf *fdf, t_mlx *mlx, const char title_minus[],const char title_plus[], int y)
{
    int     x = 25;
    int     height = 17;
    void    *img_minus;
    void    *img_plus;

   img_plus = mlx_xpm_file_to_image(mlx->mlx_ptr, (char*)title_plus, &x, &height);
   img_minus = mlx_xpm_file_to_image(mlx->mlx_ptr, (char*)title_minus, &x, &height);
   if (!img_minus || !img_plus)
        printf("NOOOOOO CRASH image non trouver %s, %s\n", title_plus, title_minus);
   else
   {
       mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, img_plus, mlx->width_menu * 2 / 3, y - 10);
       mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, img_minus, mlx->width_menu / 20, y);
   }
   return (1);
}

int         put_subtitle(t_fdf *fdf, t_mlx *mlx, const char title[], int y, t_option option)
{
    int color;

    color = set_r(0, 255);
    if ( (option == 	PROJECTION_ORTHO && fdf->type_projection == ORTHO)
	       || (option == PROJECTION_ISOMETRIC && fdf->type_projection == ISOMETRIC)
	       || (option == PROJECTION_PARALLELE && fdf->type_projection == PARALLELE))
           color = set_g(0, 255);
    mlx_string_put(mlx->mlx_ptr, mlx->win, mlx->width_menu / 4, y, color, (char*)title);
    return 1;
}

int         put_title(t_fdf *fdf, t_mlx *mlx, const char title[], int y, int color)
{
    mlx_string_put(mlx->mlx_ptr, mlx->win, mlx->width_menu / 5, y, color, (char*)title);
    return 1;
}

void        draw_option(t_fdf *fdf, const t_menu type[], const char name[GRID_NB][20], const t_option options[])
{
    int     i;
    t_mlx   *mlx;

    i = 0;
    mlx = fdf->mlx;
    while (i < GRID_NB)
    {
        if (type[i] == TITLE)
            put_title(fdf, mlx, name[i], i * mlx->size_y / GRID_SIZE,  set_b(0, 255));
        if (type[i] == SUB_TITLE)
            put_subtitle(fdf, mlx, name[i], i * mlx->size_y / GRID_SIZE, options[i]);
        if (type[i] == GRADUATION)
        {
            put_graduation(fdf, mlx, name[i], name[i+1],  i * mlx->size_y / GRID_SIZE);
            i++;
        }
        i ++;
    }
}

void        draw_menu(t_fdf *fdf)
{   
    int     i;
    t_mlx   *mlx;
    
    const t_menu type[GRID_NB] = {NOTHING, NOTHING, NOTHING, TITLE, SUB_TITLE,  SUB_TITLE,  SUB_TITLE, NOTHING, 
        TITLE, GRADUATION, GRADUATION, TITLE, GRADUATION, GRADUATION, TITLE, GRADUATION, GRADUATION, TITLE, GRADUATION, GRADUATION};
    const char name[GRID_NB][20] = {"", "", "", "PROJECTION", "ORTHO",  "ISOMETRIC",  "PARALLELE", "", 
        "ZOOM", MINUS_BUTTON_NAME, PLUS_BUTTON_NAME, "DEPTH", MINUS_BUTTON_NAME, PLUS_BUTTON_NAME,  "ROTATION_STEP", MINUS_BUTTON_NAME, PLUS_BUTTON_NAME,  "MOVE_STEP", MINUS_BUTTON_NAME, PLUS_BUTTON_NAME};
    const t_option options[GRID_SIZE] = {EMPTY, EMPTY, EMPTY, PROJECTION_TYPE, PROJECTION_ORTHO, PROJECTION_ISOMETRIC, PROJECTION_PARALLELE, EMPTY,
         ZOOM_STEP, ZOOM_STEP, ZOOM_STEP, DEPTH_STEP, DEPTH_STEP, DEPTH_STEP, ROTATION_STEP, ROTATION_STEP, ROTATION_STEP, MOVE_STEP, MOVE_STEP, MOVE_STEP};

    mlx = fdf->mlx;
    i = 0;
    draw_menu_background(fdf->mlx); // also clear img
    draw_menu_graduation(fdf, mlx, type, options);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img_menu, 0, 0);
    draw_option(fdf, type, name, options);
}   