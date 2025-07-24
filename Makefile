# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/18 12:10:58 by arina             #+#    #+#              #
#    Updated: 2025/07/24 13:45:50 by mabaghda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3
LDFLAGS = -lreadline

SRCS = main.c list.c functions.c tokenization.c quotes.c
OBJS = $(SRCS:.c=.o)

GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[1;33m
RED = \033[0;31m
VIOLET = \033[38;5;99m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(BLUE)[LINKING]$(RESET) 🔗 Building $(GREEN) $(NAME) $(RESET)..."
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS) $(LIBFT)
	@echo "$(YELLOW)MINISHELL IS READY!$(RESET)"


$(LIBFT):
	@echo "$(VIOLET)COMPILING LIBFT...$(RESET)"
	@make --no-print-directory -C $(LIBFT_DIR)
	@echo "$(GREEN)[OK]$(RESET) ✅ LIBFT DONE."

%.o: %.c $(LIBFT) minishell.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)[CLEAN]$(RESET) Removing object files..."
	@make --no-print-directory -C $(LIBFT_DIR) clean
	@rm -f $(OBJS)
	@echo "$(GREEN)[OK]$(RESET) ✅ Clean done."

fclean: clean
	@echo "$(YELLOW)[FCLEAN]$(RESET) Removing executable and libft..."
	@make --no-print-directory -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "$(GREEN)[OK]$(RESET) ✅ Full clean done."


re: fclean all

.PHONY: all clean fclean re
