NAME = cub3D

CC = cc

FLAGS =   -Wall -Wextra -Werror 

SRCS = main.c \
		parcing/parse.c \
		parcing/check_data.c \
		parcing/check_data2.c \
		parcing/map_init.c \
		parcing/extra_sauce.c \
		parcing/parse_2.c \
		parcing/parse_map2.c \
		parcing/mooore.c \
		parcing/more1.c \
		parcing/tools_2.c \
		parcing/tools.c \
		parcing/get_next_line.c \
		parcing/get_next_line_utils.c \
		parcing/parse_map.c \
    	recasting/tracing.c \
		recasting/tractools.c \
		recasting/recastinit.c \
		recasting/keys_control.c \
		recasting/keys_control2.c \
		recasting/keys_control3.c \
		recasting/player.c \
		recasting/cast.c \
		recasting/cast2.c \
		recasting/horizontal.c \
		recasting/vertical.c \
		set_textures/load_texts.c \
		set_textures/sprites.c \
		free_leaks.c


OBJS = $(SRCS:.c=.o)


all: $(NAME)

MLX_LIB = libmlx42.a
GLFW_LIB = libglfw3.a

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o : %.c ./cub3D.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONEY : clean