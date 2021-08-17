#include "fdf.h"

/*
#define GRID_SIZE 30
#define GRID_NB 20
#define SIZE_BUTTON 45
#define GRADUATION_SIZE 5
#define GRADUATION_BACKGROUND_COLOR 8355711
*/
//#define SPACE_BUTON 
//#define GRID_SIZE 8


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

int         draw_menu_zoom(t_fdf *fdf, t_mlx *mlx, int y)
{
    mlx_string_put(mlx->mlx_ptr, mlx->win, mlx->width_menu / 5, y, set_b(0, 255), "ZOOM");
    return y;
}

int        draw_menu_projection(t_fdf *fdf, t_mlx *mlx, int y)
{
        //printf("%d\n", fdf->type_projection);
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
	int i;
	int j;
    int index;
    int graduation_index;
    int add_pos;
    
	i = 0;
    graduation_index = 0;
    add_pos = (!fdf->button_grad_y) ? 1 : 0;
	if (add_pos)
        fdf->button_grad_y = ft_memalloc(sizeof(int) * GRADUATION_SIZE);
    index = -1;
    while (++index < GRID_NB)
    {
        if (type[index] == GRADUATION)
        {
            i = index * mlx->size_y / GRID_SIZE;
            if (add_pos)
                fdf->button_grad_y[graduation_index++] = i;
            draw_graduation( fdf, mlx, i, (index + 1) * mlx->size_y / GRID_SIZE, options[index]);
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
   //printf("plus size w(%d), h(%d)\n", x, height);
   img_minus = mlx_xpm_file_to_image(mlx->mlx_ptr, (char*)title_minus, &x, &height);
   //printf("minus size w(%d), h(%d)\n", x, height);
   if (!img_minus || !img_plus)
        printf("NOOOOOO CRASH image non trouver %s, %s\n", title_plus, title_minus);
   else
   {
       mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, img_plus, mlx->width_menu * 2 / 3, y - 10);
       mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, img_minus, mlx->width_menu / 20, y);
       //printf("img pos_x %d %d\n", mlx->width_menu / 20, mlx->width_menu / 20 + x);

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

void        draw_menu(t_fdf *fdf)
{   
    int     i;
    t_mlx   *mlx;
    
    const t_menu type[GRID_NB] = {NOTHING, NOTHING, NOTHING, TITLE, SUB_TITLE,  SUB_TITLE,  SUB_TITLE, NOTHING, 
        TITLE, GRADUATION, GRADUATION, TITLE, GRADUATION, GRADUATION, TITLE, GRADUATION, GRADUATION, TITLE, GRADUATION, GRADUATION};
    const char name[GRID_NB][20] = {"", "", "", "PROJECTION", "ORTHO",  "ISOMETRIC",  "PARALLELE", "", 
        "ZOOM", "minusbutton.xpm", "plusbutton.xpm", "DEPTH", "minusbutton.xpm", "plusbutton.xpm",  "ROTATION_STEP", "minusbutton.xpm", "plusbutton.xpm",  "MOVE_STEP", "minusbutton.xpm", "plusbutton.xpm"};
    const t_option options[GRID_SIZE] = {EMPTY, EMPTY, EMPTY, PROJECTION_TYPE, PROJECTION_ORTHO, PROJECTION_ISOMETRIC, PROJECTION_PARALLELE, EMPTY,
         ZOOM_STEP, ZOOM_STEP, ZOOM_STEP, DEPTH_STEP, DEPTH_STEP, DEPTH_STEP, ROTATION_STEP, ROTATION_STEP, ROTATION_STEP, MOVE_STEP, MOVE_STEP, MOVE_STEP};

    mlx = fdf->mlx;
    i = 0;
    draw_menu_background(fdf->mlx); // also clear img
    draw_menu_graduation(fdf, mlx, type, options);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img_menu, 0, 0);
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