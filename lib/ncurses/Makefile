##
## EPITECH PROJECT, 2024
## MiniLibC
## File description:
## Makefile
##

CC = g++

FPIC = -c -fPIC

CFLAGS = -shared

NCURSES = -lncurses

SRC  =	NCurses.cpp

OBJ = $(SRC:.cpp=.o)

NAME = libncurses.so

all:   	$(NAME)

$(NAME):    $(OBJ)
	$(CC) $(FPIC) $(SRC)
	$(CC) $(CFLAGS) $(NCURSES) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:    fclean all

.PHONY: all clean fclean re