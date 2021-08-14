NAME = fdf
NAME_OPTION = option_fdf

INC=/usr/lib



INCLUDE= -I. -Iminilibx-linux

SRCS = colors.c  draw_menu.c  init.c \
       parsing.c utils.c draw.c event.c main.c rotation.c

SRCS_OPTION = utils_getcode.c colors.c

OBJ = $(SRCS:%.c=%.o)
OBJ_OPTION = $(SRCS_OPTION:%.c=%.o)




CFLAGS = -Wall -lmlx -lXext -lX11 -lm -lbsd  -Lminilibx-linux -L$(INC) $(INCLUDE)


all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS) libft.a

$(NAME_OPTION): $(OBJ_OPTION)
	gcc -o $(NAME_OPTION) $(OBJ_OPTION) $(CFLAGS)

clean:
	rm -f $(NAME) $(NAME_OPTION) $(OBJ)

re: clean all
