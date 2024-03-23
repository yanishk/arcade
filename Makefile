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

CXXFLAGS = -I include/ -I display/ -I games/ -I core/ -Wall -Wextra -g

NAME = arcade

all: core games graphicals

clean: games_clean graphicals_clean core_clean

fclean: games_fclean graphicals_fclean core_fclean

re: fclean all

core: $(NAME)

$(NAME):	$(OBJ)
	$(CXX) -o $(NAME) $(OBJ)

core_clean:
	$(RM) $(OBJ)

core_fclean: core_clean
	$(RM) $(NAME)

games:
	cd games/Nibbler && make
	cd games/Pacman && make

games_clean:
	cd games/Nibbler && make clean
	cd games/Pacman && make clean

games_fclean:
	cd games/Nibbler && make fclean
	cd games/Pacman && make fclean

graphicals:
	cd display/ncurses && make
	cd display/sdl2 && make
	cd display/sfml && make

graphicals_clean:
	cd display/ncurses && make clean
	cd display/sdl2 && make clean
	cd display/sfml && make clean

graphicals_fclean:
	cd display/ncurses && make fclean
	cd display/sdl2 && make fclean
	cd display/sfml && make fclean

.PHONY :  all clean fclean re core games graphicals
