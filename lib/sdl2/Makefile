##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC = SDL2.cpp

OBJ = $(SRC:.cpp=.o)

CXX = g++

CXXFLAGS = -fPIC -I /usr/include/SDL2 -I .. -I ../../

LDFLAGS = -shared

LDLIBS = -lSDL2 -lSDL2_ttf

NAME = sdl2.so

all : $(NAME)

$(NAME):	$(OBJ)
	$(CXX) -c $(CXXFLAGS) $(SRC)
	$(CXX) $(LDFLAGS) -o $(NAME) $(LDLIBS) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY : all clean fclean re
