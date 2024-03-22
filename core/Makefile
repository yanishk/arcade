##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC =	core/Core.cpp 	\
		main.cpp


OBJ = $(SRC:.cpp=.o)

CXX = g++

CXXFLAGS = -I . -I display/ -I games/ -I core/

NAME = arcade

all: games

#core

#core: $(NAME)

#$(NAME):	$(OBJ)
#	$(CXX) -o $(NAME) $(OBJ)

games:
	cd games/Nibbler && make re

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY : all clean fclean re
