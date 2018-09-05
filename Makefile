# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikotvits <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/17 17:44:05 by ikotvits          #+#    #+#              #
#    Updated: 2018/07/17 17:44:06 by ikotvits         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --silent

NAME = lem-in

FLAGS = -Wall -Wextra -Werror

LIB_DIR = libft/

SRCS = ants_way.c lem_alg.c lem_in_extra.c lem_in.c ways.c

DIR = lem_in_dir/

SRC = $(addprefix $(DIR), $(SRCS))

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(addprefix $(DIR), lem_in.h)
	make -C $(LIB_DIR)
	gcc $(OBJ) -o $(NAME) -L $(LIB_DIR) -lft
	tput setaf 3; echo "Binary file has been created"

%.o: $(DIR)%.c
	gcc -c $(FLAGS) -o $@ -c $< -I $(DIR)

clean:
	rm -f $(OBJ)
	make -C ./libft clean
	tput setaf 4; echo All object files have been deleted

fclean: clean
	rm -f $(NAME)
	make -C ./libft fclean
	tput setaf 5; echo Binary file has been deleted

re: fclean all