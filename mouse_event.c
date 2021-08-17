#include "fdf.h"








void     process_button(t_fdf *fdf, int is_plus, t_option option)
{
    if (option == MOVE_STEP && is_plus && fdf->infos.step_size * fdf->infos.zoom * fdf->infos.zoom_y < SIZE_HEIGHT)
        fdf->infos.step_size = ((fdf->infos.step_size+1) * fdf->infos.zoom * fdf->infos.zoom_y < SIZE_HEIGHT)
            ? fdf->infos.step_size + 1 : SIZE_HEIGHT / (fdf->infos.zoom * fdf->infos.zoom_y) ;
    if (option == MOVE_STEP && !is_plus && fdf->infos.step_size > 1)
        fdf->infos.step_size --;

    if (option == ZOOM_STEP && is_plus && fdf->infos.zoom_pas < 10)
        fdf->infos.zoom_pas ++;
    if (option == ZOOM_STEP && !is_plus && fdf->infos.zoom_pas > 1)
        fdf->infos.zoom_pas --;

    if (option == DEPTH_STEP && is_plus && fdf->infos.deep_pas < 10)
        fdf->infos.deep_pas += 1;
    if (option == DEPTH_STEP && !is_plus && fdf->infos.deep_pas > 1)
        fdf->infos.deep_pas -= 1;

    if (option == ROTATION_STEP && is_plus && fdf->angle.pas == 118)
        fdf->angle.pas = 120;
    else if (option == ROTATION_STEP && !is_plus && fdf->angle.pas == 120)
        fdf->angle.pas = 118;
    else if (option == ROTATION_STEP && is_plus && fdf->angle.pas < 112)
        fdf->angle.pas += 12;
    else if (option == ROTATION_STEP && !is_plus && fdf->angle.pas > 10)
        fdf->angle.pas -= 12;
    
    process_draw(fdf);
}

/*
    mouse pressed
 */
int     mouse_event(int button, int x, int y, void *param)
{
    t_fdf           *fdf;
    int             i;
    int             width;
    const t_option  options[GRADUATION_SIZE] = {ZOOM_STEP, DEPTH_STEP, ROTATION_STEP, MOVE_STEP};

    fdf = (t_fdf*)param;
    i = -1;
    width = fdf->mlx->width_menu;
    while (++i < GRADUATION_SIZE)
    {
        if (fdf->button_grad_y > 0 && y > fdf->button_grad_y[i] && y <  fdf->button_grad_y[i] + SIZE_BUTTON 
                && ((x >  width / 20 &&  x < width / 20 + BUTTON_LEFT_W) || (x >  width * 2 / 3 && x <  width * 2 / 3 + BUTTON_RIGHT_W)))
            process_button(fdf, x >  width * 2 / 3 && x <  width * 2 / 3 + BUTTON_RIGHT_W, options[i]);
    }
    return 1;
}