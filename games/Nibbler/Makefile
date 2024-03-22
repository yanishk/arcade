##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC = Nibbler.cpp

OBJ = $(SRC:.cpp=.o)

CXX = g++

CXXFLAGS = -fPIC -I .. -I ../../include

LDFLAGS = -shared

LDLIBS = -lncurses

LIBPATH = ../../lib/

NAME = nibbler.so

all : $(NAME)

$(NAME):	$(OBJ)
	$(CXX) -c $(CXXFLAGS) $(SRC)
	$(CXX) $(LDFLAGS) -o $(NAME) $(LDLIBS) $(OBJ)
	cp $(NAME) $(LIBPATH)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBPATH)/$(NAME)

re: fclean all

.PHONY : all clean fclean re
