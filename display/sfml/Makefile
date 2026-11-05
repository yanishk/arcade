##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC = Sfml.cpp

OBJ = $(SRC:.cpp=.o)

CXX = g++

CXXFLAGS = -fPIC -I /usr/include/SFML -I .. -I ../../include -Wall -Wextra -std=c++17

LDFLAGS = -shared

LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

LIBPATH = ../../lib/

NAME = arcade_sfml.so

all : $(NAME)

$(NAME):	$(OBJ)
	$(CXX) -c $(CXXFLAGS) $(SRC)
	$(CXX) $(LDFLAGS) -o $(NAME) $(OBJ) $(LDLIBS)
	cp $(NAME) $(LIBPATH)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBPATH)/$(NAME)

re: fclean all

.PHONY : all clean fclean re
