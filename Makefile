# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/18 12:10:58 by arina             #+#    #+#              #
#    Updated: 2025/07/25 11:19:32 by mabaghda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
LDFLAGS = -lreadline

SRCS = main.c list.c functions.c tokenization.c quotes.c
OBJS = $(SRCS:.c=.o)

GREEN = \033[1;28;5;32m
BLUE = \033[0;34m
YELLOW = \033[0;33m
VIOLET = \033[38;5;60m
IDK = \033[1;38;5;34m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(BLUE)[LINKING]$(RESET) Building $(GREEN) $(NAME) $(RESET)..."
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS) $(LIBFT)
	@echo "$(IDK)      MINISHELL IS READY!$(RESET)"


$(LIBFT):
	@echo "$(BLUE)COMPILING LIBFT...$(RESET)"
	@make --no-print-directory -C $(LIBFT_DIR)
	@echo "$(GREEN) [OK]$(RESET) libft done."

%.o: %.c $(LIBFT) minishell.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)[CLEAN]$(RESET) Removing object files..."
	@make --no-print-directory -C $(LIBFT_DIR) clean
	@rm -f $(OBJS)
	@echo "$(GREEN) [OK]$(RESET) Clean done."

fclean: clean
	@echo "$(YELLOW)[FCLEAN]$(RESET) Removing executable and libft..."
	@make --no-print-directory -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "$(GREEN) [OK]$(RESET) Full clean done."


re: fclean all

.PHONY: all clean fclean re
