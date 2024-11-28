CC = cc
CFLAGS = -Wall -Wextra -Werror 
SRCS = main.c parse.c check_data.c list_init.c parse_2.c mooore.c tools_2.c tools.c get_next_line.c get_next_line_utils.c
OBJS = $(SRCS:.c=.o)
NAME = cube3d
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c cube3d.h 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONEY : clean