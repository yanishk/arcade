##
## EPITECH PROJECT, 2024
## MiniLibC
## File description:
## Makefile
##

CC = g++

FPIC = -c -fPIC

CFLAGS = -shared

SRC  =	SDL2.cpp

SDL = -lSDL2 -lSDL2_ttf

OBJ = $(SRC:.cpp=.o)

NAME = libsdl2.so

all:   	$(NAME)

$(NAME):    $(OBJ)
	$(CC) $(FPIC) $(SRC)
	$(CC) $(CFLAGS) $(SDL) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:    fclean all

.PHONY: all clean fclean re