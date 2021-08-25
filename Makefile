
NAME = fdf
NAME_OPTION = option_fdf

INC=/usr/lib
INCLUDE= -Iinclude -Iminilibx-linux

DIR_OBJ = obj
DIR_SRC = src

CFLAGS = -Wall -Wextra -lmlx -lXext -lX11 -lm -lbsd -Lminilibx-linux -L$(INC) $(INCLUDE)


SRCS_MAIN = keyboard_event.c main.c parsing.c utils.c draw.c init.c \
		draw_menu.c draw_menu_graduation.c rotation.c get_next_line2.c \
		infos.c draw_main_img.c projection.c mouse_event.c rotate_main.c\
		utils_rotate.c libft_basic.c free.c libft_memory.c libft_gnl.c

SRCS_MUTUAL = colors.c

SRCS_OPTION = utils_getcode.c


all: $(NAME) $(NAME_OPTION)

OBJ_MAIN = $(addprefix $(DIR_OBJ)/, $(patsubst %.c, %.o, $(SRCS_MAIN))) 
$(OBJ_MAIN): $(DIR_OBJ)%.o: $(DIR_SRC)%.c
	mkdir -p $(DIR_OBJ)
	gcc -o $@ $(CFLAGS) -c $<

OBJ_MUTUAL = $(addprefix $(DIR_OBJ)/, $(patsubst %.c, %.o, $(SRCS_MUTUAL))) 
$(OBJ_MUTUAL): $(DIR_OBJ)%.o: $(DIR_SRC)%.c
	mkdir -p $(DIR_OBJ)
	gcc $< $(CFLAGS) -c -o $@

OBJ_OPTION = $(addprefix $(DIR_OBJ)/, $(patsubst %.c, %.o, $(SRCS_OPTION))) 
$(OBJ_OPTION): $(DIR_OBJ)%.o: $(DIR_SRC)%.c
	mkdir -p $(DIR_OBJ)
	gcc $< $(CFLAGS) -c -o $@

OBJ_COMPLETE = $(subst $(DIR_SRC)/, $(DIR_OBJ)/, $(OBJ_MAIN)) $(subst $(DIR_SRC)/, $(DIR_OBJ)/, $(OBJ_MUTUAL))  $(subst $(DIR_SRC)/, $(DIR_OBJ)/, $(OBJ_OPTION))

#CFLAGS = -Wall -Wextra -Iinclude -framework OpenGL -framework AppKit -lmlx

$(NAME): $(OBJ_MAIN) $(OBJ_MUTUAL)
	gcc -o $(NAME) $(OBJ_MAIN) $(OBJ_MUTUAL) $(CFLAGS)

$(NAME_OPTION): $(OBJ_OPTION) $(OBJ_MUTUAL)
	gcc -o $(NAME_OPTION) $(OBJ_OPTION) $(OBJ_MUTUAL) $(CFLAGS)

clean:
	rm -f  $(OBJ) $(OBJ_COMPLETE)

fclean: clean
	rm -f $(NAME) $(NAME_OPTION)

re: fclean all
