RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
BOLD = \033[1m
END = \033[0m

NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

SRC = parse.c main.c utils.c err_message.c verife_must_element.c\
	utils_V1.c ft_free.c map_utils.c\

GET_NEXT_LINE = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

H_LIBFT = libft.h

G_HEADER = get_next_line/get_next_line.h

HEADER = cub3d.h

EXE_LIBFT =	libft/libft.a

OBJ = $(SRC:.c=.o)

all:	$(NAME)

%.o: %.c $(L_HEADER) $(G_HEADER) $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJ)
	@make -C libft/
	@echo "$(GREEN)$(BOLD)    [ libft archived ]$(END)"
	@$(CC) $(CFLAGS) $(SRC) $(GET_NEXT_LINE) $(EXE_LIBFT) -o $(NAME)
	@sleep 1
	@echo "$(BOLD)$(YELLOW)    [ Cub3D compiled ] $(END)"

clean:
	@make clean -C libft/
	@rm -f $(OBJ)
	@echo "$(RED)$(BOLD)       [ Cleaned up object files ]$(END)"

fclean:	clean
	@make fclean -C libft/
	@rm -rf $(NAME)

re:	fclean all

.PHONY: all clean fclean re

