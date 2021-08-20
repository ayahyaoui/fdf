
#ifndef __CONSTANTE_H__
#define __CONSTANTE_H__



#define ESC 53
#define LEFT 123
#define RIGHT 124
#define DOWN 125
#define UP 126
#define ZOOM 69
#define UNZOOM 78
#define QUIT 12
#define X_RIGHT 85
#define X_LEFT 83
#define Y_RIGHT 88
#define Y_LEFT 86
#define Z_RIGHT 92
#define Z_LEFT 89
#define INFOS 34
#define DEEPER 13
#define SHALLOWER 7
#define NEXT_PROJECTION 45

#define GRID_SIZE 30
#define GRID_NB 20
#define SIZE_BUTTON 65
#define BUTTON_LEFT_W 45
#define BUTTON_RIGHT_W 65
#define GRADUATION_SIZE 5
#define GRADUATION_BACKGROUND_COLOR 8355711
#define SIZE_HEIGHT 1350

typedef enum       e_menu
{
    NOTHING,
    TITLE,
    SUB_TITLE,
    GRADUATION
}                  t_menu;

typedef enum       e_option
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
}                  t_option;


typedef enum    e_type_rotation
{
    ROTATION_X, 
    ROTATION_Y,
    ROTATION_Z
}               t_type_rotation;


#endif