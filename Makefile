NAME = rdp_calc

SRC = main.c lexer.c parser.c display.c

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	cc -o $@ $^

%.o: %.c
	cc -c $< -o $@ -I include/

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: re
	./$(NAME)

# alias
cl: clean
fcl: fclean
