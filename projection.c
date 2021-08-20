
#include "fdf.h"

/*
							TODO procees projction
*/
void	process_isometric_projection(t_fdf *fdf){
	int	y;
	int	x;

	y = 0;
	while (y < fdf->infos.y_max)
	{
		x = 1;
		while (x < fdf->map[y][0].x)
		{
			double tmp_x = (double)((fdf->map[y][x].x -fdf->map[y][x].z) /
					((double)sqrt(2)));
			double tmp_y = (double)((fdf->map[y][x].x +2 * fdf->map[y][x].y +
					fdf->map[y][x].z) / ((double)sqrt(6)));
			fdf->map[y][x].y = (int)tmp_y;
			fdf->map[y][x].x = (int)tmp_x;
			x++;
		}
		y++;
	}
}

void	change_projection(t_fdf *fdf, t_projection projection)
{
	if (projection == fdf->type_projection)
	{
		return;
	}
	if (projection == ISOMETRIC)
	{
		process_isometric_projection(fdf);
		process_draw(fdf);
		//dislplay_map_infos(fdf);
	}
}

int			process_next_projection(t_fdf *fdf)
{
	fdf->angle.x = 0;
	fdf->angle.y = 0;
	fdf->angle.z = 0;

	if (fdf->type_projection == ISOMETRIC)
	{
		fdf->type_projection = PARALLELE;
	}
	else if (fdf->type_projection == ORTHO)
	{
		fdf->type_projection = ISOMETRIC;
	}
	else
	{
		fdf->type_projection = ORTHO;
	}
	rotate_precision(fdf);
	return (1);
}