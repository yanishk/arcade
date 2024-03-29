##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC =	core/Core.cpp 		\
		main.cpp			\

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
	make -C games/Menu
	make -C games/Nibbler
	make -C games/Pacman

games_clean:
	make clean -C games/Menu
	make clean -C games/Nibbler
	make clean -C games/Pacman

games_fclean:
	make fclean -C games/Menu
	make fclean -C games/Nibbler
	make fclean -C games/Pacman

graphicals:
	make -C display/ncurses
	make -C display/sdl2
	make -C display/sfml

graphicals_clean:
	make clean -C display/ncurses
	make clean -C display/sdl2
	make clean -C display/sfml

graphicals_fclean:
	make fclean -C display/ncurses
	make fclean -C display/sdl2
	make fclean -C display/sfml

.PHONY :  all clean fclean re core games graphicals
