# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/25 18:33:02 by mgallo            #+#    #+#              #
#    Updated: 2017/04/14 15:51:23 by qhonore          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./srcs/
OBJ_PATH = ./objs/
INC_PATH = ./includes/ ~/.brew/include
LIB_PATH = ~/.brew/lib

SRC_NAME = main.cpp Debug.cpp Effect.cpp Entity.cpp Movable.cpp\
		Spell.cpp Map.cpp Game.cpp Input.cpp Player.cpp Pathfinder.cpp
OBJ_NAME = $(SRC_NAME:.cpp=.o)
LIB_NAME = -lm
NAME = game_tools

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I ,$(INC_PATH))
LIB = $(addprefix -L ,$(LIB_PATH))
FRAMEWORK = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network -lsfml-audio -Wl,-rpath,$$HOME/.brew/lib

CC = g++
CFLAGS = -O3 -flto -Wall -Wextra -Werror -pedantic -Wuninitialized -g3 -std=c++11

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(INC) $(LIB) $(LIB_NAME) $(FRAMEWORK)

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

git : fclean pull
	git add .

pull:
	git fetch
	git pull

install:
	# rm -rf ~/.brew
	brew update
	brew upgrade
	brew install sfml

.PHONY: all clean fclean re
