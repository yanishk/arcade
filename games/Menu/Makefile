##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC = Menu.cpp

OBJ = $(SRC:.cpp=.o)

CXX = g++

CXXFLAGS = -fPIC -I .. -I ../../include -Wall -Wextra

LDFLAGS = -shared

LIBPATH = ../../lib/

NAME = arcade_menu.so

all : $(NAME)

$(NAME):	$(OBJ)
	$(CXX) -c $(CXXFLAGS) $(SRC)
	$(CXX) $(LDFLAGS) -o $(NAME) $(OBJ)
	cp $(NAME) $(LIBPATH)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBPATH)/$(NAME)

re: fclean all

.PHONY : all clean fclean re
