##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC = Nibbler.cpp

OBJ = $(SRC:.cpp=.o)

CXX = g++

CXXFLAGS = -fPIC -I ..

LDFLAGS = -shared

LDLIBS = -lncurses

NAME = nibbler.so

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
