SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

CC = gcc
LD = gcc

CFLAGS = -Wall -Wextra -Iinclude -fPIC -g
LDFLAGS = 
LIBS = oeuf/liboeuf.a

NAME = stc

all: $(NAME)

$(NAME): $(OBJ) $(LIBS)
	$(LD) -o $(NAME) $(OBJ) $(LIBS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

oeuf/liboeuf.a:
	make -C oeuf

clean:
	rm -rf $(OBJ)
	make clean -C oeuf/

fclean: clean
	rm $(NAME) 
	make fclean -C oeuf/

re: fclean all

.PHONY: re fclean clean all test
