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

CXXFLAGS = -I lib/

NAME = arcade

all : $(NAME)

$(NAME):	$(OBJ)
	$(CXX) -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY : all clean fclean re
