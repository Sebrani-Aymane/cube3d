CC = cc

FLAGS = -Wall -Wextra -Werror   -fsanitize=address -g

SRCS = main.c \
		parse.c \
		check_data.c \
		map_init.c \
		extra_sauce.c \
		parse_2.c \
		parse_map2.c \
		mooore.c \
		tools_2.c \
		tools.c \
		get_next_line.c \
		get_next_line_utils.c \
		parse_map.c \
    	tracing.c \
		tractools.c \
		pov.c \
		recastinit.c \
		keys_control.c \
		draw.c \
		cast.c \
		cast2.c \
		set_textures/load_texts.c\


OBJS = $(SRCS:.c=.o)

NAME = cube3d

all: $(NAME)

MLX_LIB = libmlx42.a
GLFW_LIB = libglfw3.a
#FRAMEWORK =  $(MLX_LIB) $(GLFW_LIB) -O3 -g -ffast-math -Ofast -framework Cocoa -framework OpenGL -framework IOKit -lglfw3

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c cube3d.h 
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONEY : clean