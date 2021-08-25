/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constante.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 19:23:32 by anyahyao          #+#    #+#             */
/*   Updated: 2021/08/22 19:23:34 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTE_H
# define CONSTANTE_H

# define ESC 65307
/*
 * Commente l'ancienne version
 */
/*
# define LEFT 123
# define RIGHT 124
# define DOWN 125
# define UP 126
# define ZOOM 69
# define UNZOOM 78
# define QUIT 12
# define X_RIGHT 85
# define X_LEFT 83
# define Y_RIGHT 88
# define Y_LEFT 86
# define Z_RIGHT 92
# define Z_LEFT 89
# define INFOS 34
# define DEEPER 13
# define SHALLOWER 7
# define NEXT_PROJECTION 45
*/
/*
 * coller les define sous ce commentaire
 */
# define LEFT 65361
# define RIGHT 65363
# define DOWN 65364
# define UP 65362
# define ZOOM 61
# define UNZOOM 45
# define QUIT 113
# define X_RIGHT 50
# define X_LEFT 49
# define Y_RIGHT 52
# define Y_LEFT 51
# define Z_RIGHT 54
# define Z_LEFT 53
# define INFOS 105
# define DEEPER 112
# define SHALLOWER 109
# define NEXT_PROJECTION 110
/*
 * coller les define au dessus de ce commentaire
 */

# define GRID_SIZE 30
# define GRID_NB 19
# define SIZE_BUTTON 65
# define BUTTON_LEFT_W 45
# define BUTTON_RIGHT_W 65
# define GRADUATION_SIZE 5
# define GRADUATION_BACKGROUND_COLOR 8355711
# define SIZE_HEIGHT 1350

typedef enum e_menu
{
	NOTHING,
	TITLE,
	SUB_TITLE,
	GRADUATION
}	t_menu;

typedef enum e_option
{
	EMPTY,
	PROJECTION_TYPE,
	ZOOM_STEP,
	ROTATION_STEP,
	MOVE_STEP,
	DEPTH_STEP,
	PROJECTION_ORTHO,
	PROJECTION_ISOMETRIC,
	PROJECTION_PARALLELE
}	t_option;

typedef enum e_type_rotation
{
	ROTATION_X,
	ROTATION_Y,
	ROTATION_Z
}	t_type_rotation;

#endif
