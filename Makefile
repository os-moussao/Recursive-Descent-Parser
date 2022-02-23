NAME = rdp_calc

SRC = main.c lexer.c parser.c display.c eval.c

OBJ = $(SRC:%.c=%.o)

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	cc $(CFLAGS) -o $@ $^

%.o: %.c
	cc $(CFLAGS) -o $@ -c $< -I include/

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: re
	./$(NAME)

debug:
	cc -g $(SRC) -I include -o $(NAME)

# alias
cl: clean
fcl: fclean
