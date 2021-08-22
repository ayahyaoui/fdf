NAME = fdf
NAME_OPTION = option_fdf

INC=/usr/lib
INCLUDE= -Iinclude -Iminilibx-linux

DIR_OBJ = obj

SRCS = colors.c keyboard_event.c main.c parsing.c utils.c draw.c init.c \
		draw_menu.c draw_menu_graduation.c rotation.c mouse_event.c \
		infos.c draw_main_img.c isometric_projection.c projection.c free.c

SRCS_OPTION = utils_getcode.c colors.c

OBJ = $(addprefix src/, $(patsubst %.c, %.o, $(SRCS))) 

OBJ_OPTION = $(addprefix src/, $(patsubst %.c, %.o, $(SRCS_OPTION))) 

#CFLAGS =  -Iinclude -framework OpenGL -framework AppKit -lmlx
CFLAGS = -Wall -Wextra -lmlx -lXext -lX11 -lm -lbsd  -Lminilibx-linux -L$(INC) $(INCLUDE)


all: $(NAME) $(NAME_OPTION)

$(NAME): $(OBJ)
	mkdir -p $(DIR_OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS) libft.a

$(NAME_OPTION): $(OBJ_OPTION)
	gcc -o $(NAME_OPTION) $(OBJ_OPTION) $(CFLAGS)
	mv $(OBJ) $(DIR_OBJ)

clean:
	rm -f $(NAME) $(NAME_OPTION) $(OBJ) $(DIR_OBJ)/*

re: clean all
