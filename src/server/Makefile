CFLAGS = -Wall -Wextra -I../../includes/ -I. -I../../oeuf -g
CC = gcc
LD = gcc

SRC = $(wildcard *.c ../utils/*.c)
OBJ = $(SRC:.c=.o) ../../oeuf/liboeuf.a

NAME = server

all: $(NAME)

$(NAME): $(OBJ)
	$(LD) $^ -o $@

../../oeuf/liboeuf.a:
	make -C ../../oeuf/

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm $(OBJ) -rf

fclean: clean
	rm $(NAME) -rf

re: fclean all

run: $(NAME)
	./$(NAME)

.PHONY: re fclean clean all run
