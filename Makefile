# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arina <arina@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/18 12:10:58 by arina             #+#    #+#              #
#    Updated: 2025/07/30 18:47:05 by arina            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
LDFLAGS = -lreadline

SRCS = main.c list.c functions.c tokenization.c quotes.c built_in.c
OBJS = $(SRCS:.c=.o)

GREEN = \033[1;28;5;32m
BLUE = \033[1;34m
YELLOW = \033[0;33m
BABY_PINK := \033[38;2;244;194;194m
LIGHT_PINK  := \033[38;2;255;182;193m
HOT_PINK    := \033[38;2;255;105;180m
DEEP_PINK   := \033[1;38;2;255;20;147m
IDK = \033[1;38;5;34m
RESET = \033[0m


MINT_GREEN     := \033[38;2;152;255;152m
SAGE_GREEN     := \033[38;2;178;172;136m
EMERALD_GREEN  := \033[1;38;2;80;200;120m
FOREST_GREEN   := \033[1;38;2;34;139;34m
OLIVE_GREEN    := \033[38;2;128;128;0m


all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(HOT_PINK)[LINKING]$(RESET) Building $(EMERALD_GREEN) $(NAME) $(RESET)..."
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS) $(LIBFT)
	@echo "$(DEEP_PINK)      MINISHELL IS READY!$(RESET)"


$(LIBFT):
	@echo "$(HOT_PINK)COMPILING LIBFT...$(RESET)"
	@make --no-print-directory -C $(LIBFT_DIR)
	@echo "$(FOREST_GREEN) [OK]$(RESET) libft done."

%.o: %.c $(LIBFT) minishell.h Makefile
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(BLUE)[CLEAN]$(RESET) Removing object files..."
	@make --no-print-directory -C $(LIBFT_DIR) clean
	@rm -f $(OBJS)
	@echo "$(FOREST_GREEN) [OK]$(RESET) Clean done."

fclean: clean
	@echo "$(BLUE)[FCLEAN]$(RESET) Removing executable and libft..."
	@make --no-print-directory -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "$(FOREST_GREEN) [OK]$(RESET) Full clean done."


re: fclean all

.PHONY: all clean fclean re
