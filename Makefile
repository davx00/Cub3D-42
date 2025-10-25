# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: despanol <despanol@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/11 00:00:00 by despanol          #+#    #+#              #
#    Updated: 2025/10/23 15:46:33 by despanol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
RESET = \033[0m

# Program name
NAME = cub3D

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address
INCLUDES = -I./include -I./include/libft -I./minilibx-linux
LIBS = -L./include/libft -lft -L./minilibx-linux -lmlx -lXext -lX11 -lm

# Directories
SRC_DIR = .
OBJ_DIR = obj
LIBFT_DIR = include/libft
MLX_DIR = minilibx-linux

# Source files
SRCS = main.c \
	Engine/main_engine.c \
	include/free/free_one.c \
	include/free/free_two.c \
	Parse/parser/file_parser.c \
	Parse/parser/is_a_valid_map.c \
	Parse/main_parsing.c \
	Parse/parser/parse_map.c \
	Parse/parser/player.c \
	Parse/parser_aux/is_a_valid_map_aux.c \
	Parse/parser_aux/aux_minimal_functions.c \
	Parse/parser_aux/aux_valid_map.c \
	Parse/parser_aux/error.c \
	Parse/parser_aux/file_parser_aux.c \
	Parse/parser_aux/parse_map_aux.c \
	Engine/player/move_npc.c \
	Engine/player/player_controls.c \
	Engine/print/init_textures.c \
	Engine/print/draw_ceiling_floor.c \
	Engine/print/print_scene_aux.c \
	Engine/print/print_scene.c \
	Engine/raycasting/dda.c \
	Engine/raycasting/raycasting.c

# Object files
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@echo "$(CYAN)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "$(BLUE)Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@echo "$(GREEN)✓ libft compiled!$(RESET)"

$(MLX):
	@echo "$(BLUE)Building minilibx...$(RESET)"
	@$(MAKE) -C $(MLX_DIR) --no-print-directory 2>/dev/null || true
	@echo "$(GREEN)✓ minilibx compiled!$(RESET)"

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@$(MAKE) -C $(MLX_DIR) clean --no-print-directory 2>/dev/null || true
	@echo "$(GREEN)✓ Object files cleaned!$(RESET)"

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(GREEN)✓ Everything cleaned!$(RESET)"

re: fclean all

norm:
	@echo "$(MAGENTA)Checking norminette...$(RESET)"
	@norminette $(SRCS) include/cub3d.h || true

run: all
	@echo "$(CYAN)Running $(NAME)...$(RESET)"
	@./$(NAME)

debug: CFLAGS += -g3 -fsanitize=address
debug: re
	@echo "$(MAGENTA)Debug mode enabled$(RESET)"

.PHONY: all clean fclean re norm run debug
