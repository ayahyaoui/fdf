#include "fdf.h"
#define ZOOM_STEP_MIN 1
#define ZOOM_STEP_MAX 10
#define DEPTH_STEP_MIN 1
#define DEPTH_STEP_MAX 10
#define MOVE_STEP_MIN 1
#define MOVE_STEP_MAX SIZE_HEIGHT
#define ROTATION_STEP_MIN 1
#define ROTATION_STEP_MAX 120

double      get_proportion(t_fdf *fdf, t_option type_infos)
{
    double value;
    if (type_infos == MOVE_STEP)
    {
        value = (fdf->infos.step_size * fdf->infos.zoom * fdf->infos.zoom_y - MOVE_STEP_MIN);
        return (value / (MOVE_STEP_MAX - MOVE_STEP_MIN));
    }
    if (type_infos == ZOOM_STEP)
    {
        value = fdf->infos.zoom_pas - ZOOM_STEP_MIN;
        return (value / (ZOOM_STEP_MAX - ZOOM_STEP_MIN));
    }
    if (type_infos == DEPTH_STEP)
        return ((double)(fdf->infos.deep_pas - DEPTH_STEP_MIN) / (DEPTH_STEP_MAX - DEPTH_STEP_MIN));
    if (type_infos == ROTATION_STEP)
        return ((double)(fdf->angle.pas - ROTATION_STEP_MIN) / (ROTATION_STEP_MAX - ROTATION_STEP_MIN));
    return (0.5);
}