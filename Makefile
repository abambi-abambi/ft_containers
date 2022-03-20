# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abambi <abambi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/07 11:12:23 by abambi            #+#    #+#              #
#    Updated: 2022/02/10 13:58:10 by abambi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all re clean fclean

NAME = f

CXX = clang++

CXXFLAGS = -Wall -Werror -Wextra -std=c++98

SRC = main.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ) vector.hpp iterator.hpp map.hpp pair.hpp stack.hpp
	$(CXX) ${CXXFLAGS} $(OBJ) -I. -o $(NAME)

clean:
	rm -rf *.gch $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
