NAME = geneli

all: $(NAME)
	./$(NAME)

$(NAME): main.c get_next_line.c get_next_line.h get_next_line_utils.c Makefile
	gcc -Wall -Wextra -Werror -D BUFFER_SIZE=5 *.c -o $(NAME) 
clean:
	rm -f *.o $(NAME)
