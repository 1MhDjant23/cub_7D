RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
BOLD = \033[1m
END = \033[0m

NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror -O3 -g -fsanitize=address 


# SRC = $(shell find parsing raycasting -name "*.c")
SRC = parsing/parse.c parsing/struct_utils.c parsing/utils_element.c parsing/main.c parsing/utils.c parsing/errors.c parsing/verife_must_element.c\
        parsing/utils_V1.c parsing/ft_free.c parsing/map_utils.c  raycasting/mait.c \
		  raycasting/key_event_handler.c  raycasting/raycast_utils.c  raycasting/initialization.c raycasting/raycasting_dda.c raycasting/view_projection.c
MLX = ../../MLX42/build/libmlx42.a -I"../../MLX42/include/MLX42/MLX42.h" -lglfw -L"/Users/felhafid/.brew/opt/glfw/lib/"

H_LIBFT = libft.h

G_HEADER = parsing/get_next_line/get_next_line.h

HEADER = cub3d.h

GET_NEXT_LINE = parsing/get_next_line/get_next_line.c parsing/get_next_line/get_next_line_utils.c

EXE_LIBFT =	libft/libft.a

OBJ = $(SRC:.c=.o)

all:	$(NAME)

%.o: %.c $(L_HEADER) $(G_HEADER) $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJ)
	@make -C libft/
	@echo "$(GREEN)$(BOLD)    [ libft archived ]$(END)"
	@$(CC) $(CFLAGS) $(SRC) $(GET_NEXT_LINE) $(EXE_LIBFT) $(MLX) -o $(NAME) 
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

