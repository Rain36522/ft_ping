
NAME = ft_ping
CC = gcc
FLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
INCLUDES = -I includes/  -I libft/includes/

BLUE = \\033[1;34m
WHITE = \\033[0;37m
YELLOW = \\033[0;33m
RED = \\033[1;31m
GREEN = \\033[1;32m
RESET = "\\033[0m"

SRC = $(wildcard src/*.c)

OBJ = $(SRC:src/%.c=objet/%.o)



all : $(NAME)
	@echo "${GREEN}Compilation success${RESET}"

$(NAME): $(SRC) $(OBJ)
	@make -C libft/
	@$(CC) $(OBJ) $(FLAGS) $(LIBFT) -o $(NAME)

objet/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -c $< -o $@ $(INCLUDES)

clean:
	@make clean -C libft/
	@rm -rf objet/

fclean:
	@make fclean -C libft/
	@rm -rf objet/
	@rm -f $(NAME)

re: fclean all

init:
	git submodule init
	git submodule update

.PHONY : fclean re all header init