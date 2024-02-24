BLUE = \033[0;94m
GREEN = \e[1;92m
RED = \033[0;91m
RESET = \033[1;30m
WHITE = \033[1;97m
YELLOW = \033[1;33m

EMOJI_PACKAGE = \360\237\223\246
EMOJI_HAMMER = \360\237\224\250
EMOJI_TRASH = \360\237\227\221\357\270\217

NAME = cub3D

CC = cc
CFLAGS = -Werror -Wextra -Wall -O3 -g
ARGS = test.cub
ARGS2 = maps/test.cub maps/testcopy.cub

MINILIBX_PATH = minilibx-linux/
MINILIBX_NAME = libmlx.a
MINILIBX = $(MINILIBX_PATH)$(MINILIBX_NAME)

LIBFT_PATH = libft/
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_PATH)$(LIBFT_NAME)

INC = -I ./includes/
SRC_PATH = src/
OBJ_PATH = obj/

SRC = $(addprefix $(SRC_PATH), \
		main.c \
		parse/parce.c \
		parse/textures.c \
		parse/colors.c \
		parse/matrix.c \
		parse/player.c \
		parse/floodfill.c \
		vectors/vectors_utils.c \
		vectors/vectors_utils2.c \
		engine/engine.c \
		engine/engine_utils.c \
		drawing_utils.c \
		events/events.c) 

$(OBJ): $(OBJ_PATH)

OBJ = $(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@printf "$(EMOJI_HAMMER)	$(BLUE)Compiling $(WHITE)$(NAME)	$(BLUE)%-33s$(WHITE)\r" $(notdir $@)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)/parse
	@mkdir -p $(OBJ_PATH)/vectors
	@mkdir -p $(OBJ_PATH)/engine
	@mkdir -p $(OBJ_PATH)/events


$(LIBFT):
	@make -sC $(LIBFT_PATH)

$(MINILIBX):
	@make -sC $(MINILIBX_PATH)

$(NAME): $(MINILIBX) $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT_PATH) -lft -L$(MINILIBX_PATH) -lmlx -L/usr/X11/lib -lX11 -lXext -lm
	@printf  "\n$(EMOJI_PACKAGE)	$(WHITE)$(NAME)			$(YELLOW)compiled$(WHITE)\n"

clean:
	@rm -rf $(OBJ_PATH)
	@make clean -sC $(LIBFT_PATH)
	@make clean -sC $(MINILIBX_PATH)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)
	@rm -f $(MINILIBX)
	@printf "$(EMOJI_TRASH)	$(WHITE)$(NAME)			$(RED)removed$(WHITE)\n"

re: fclean all

run: clean_exe all
	@./$(NAME) maps/test1.cub

v: all
	@valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME) $(ARGS)

v2: all
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(ARGS2)

clean_exe:
	@rm -rf $(OBJ_PATH)
	@rm -fr $(NAME)

.PHONY: all re clean fclean run
