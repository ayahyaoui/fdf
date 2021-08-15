
#include "fdf.h"

/*
							TODO procees projction
*/
void		process_isometric_projection(t_fdf *fdf){
	int y;
	int x;

	y = 0;
	printf("iso start\n");
	while (y < fdf->infos.y_max)
	{
		x = 1;
		while (x < fdf->map[y][0].x)
		{
/*
			fdf->map[y][x].x = (int)((fdf->original_map[y][x].x -
					fdf->original_map[y][x].z) / ((double)sqrt(2)));
			fdf->map[y][x].y = (int)((fdf->original_map[y][x].x +
			2 * fdf->original_map[y][x].y + fdf->original_map[y][x].z) /
					((double)sqrt(6)));
*/
			double tmp_x = (double)((fdf->map[y][x].x -fdf->map[y][x].z) /
					((double)sqrt(2)));
			double tmp_y = (double)((fdf->map[y][x].x +2 * fdf->map[y][x].y +
					fdf->map[y][x].z) / ((double)sqrt(6)));
			//printf("%d->%f\n", fdf->map[y][x].x, tmp_x);
			fdf->map[y][x].y = (int)tmp_y;
			fdf->map[y][x].x = (int)tmp_x;

			x++;
		}
		y++;
	}
	printf("iso finsh\n");
}


void		change_projection(t_fdf *fdf, t_projection projection)
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


