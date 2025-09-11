# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/18 12:10:58 by arina             #+#    #+#              #
#    Updated: 2025/09/11 21:13:07 by mabaghda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address
LDFLAGS = -lreadline

SRCS = main.c list.c functions.c path.c tokenization/tokenization.c \
		tokenization/init_tokens_type.c quotes/quotes.c quotes/quotes_len.c \
		quotes/quotes_helpers1.c quotes/quotes_helpers2.c \
		quotes/quotes_helpers3.c built-in/built_in.c built-in/exit.c \
		built-in/cd.c built-in/pwd.c built-in/echo.c built-in/unset.c \
		built-in/env.c built-in/export/check.c built-in/export/find_and_return.c \
		built-in/export/export_utils.c built-in/export/export.c \
		built-in/export/print.c free.c signal.c  \
		operators/redirs/redir_cmd.c operators/redirs/execute_redirs.c \
		operators/redirs/redir_helpers.c operators/heredoc.c \
		operators/pipe/pipe.c operators/pipe/pipe_fork.c operators/pipe/pipe_helper.c \
		operators/file.c
		
OBJDIR = obj
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

#GREEN = \033[1;28;5;32m
#BLUE = \033[1;34m
YELLOW = \033[0;33m
#BABY_PINK := \033[38;2;244;194;194m
#LIGHT_PINK  := \033[38;2;255;182;193m
PB := \033[38;2;255;204;213m
HOT_PINK    := \033[1;38;2;255;105;180m
DEEP_PINK   := \033[1;38;2;255;20;147m
#IDK = \033[1;38;5;34m
RESET = \033[0m

#MINT_GREEN     := \033[38;2;152;255;152m
#SAGE_GREEN     := \033[38;2;178;172;136m
EMERALD_GREEN  := \033[1;38;2;80;200;120m
#FOREST_GREEN   := \033[1;38;2;34;139;34m
#OLIVE_GREEN    := \033[38;2;128;128;0m

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) Makefile minishell.h quotes/quotes.h
	@echo "$(PB)[LINKING]$(RESET) Building $(EMERALD_GREEN) $(NAME) $(RESET)..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)
	@echo "$(DEEP_PINK)      MINISHELL IS READY!$(RESET)"

$(LIBFT):
	@echo "$(PB)COMPILING LIBFT...$(RESET)"
	@make --no-print-directory -C $(LIBFT_DIR)
	@echo "$(HOT_PINK) [OK]$(RESET) libft done."

$(OBJDIR)/%.o: %.c minishell.h Makefile
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)[CLEAN]$(RESET) Removing object files..."
	@make --no-print-directory -C $(LIBFT_DIR) clean
	@rm -rf $(OBJDIR)
	@echo "$(HOT_PINK) [OK]$(RESET) Clean done."

fclean: clean
	@echo "$(YELLOW)[FCLEAN]$(RESET) Removing executable and libft..."
	@make --no-print-directory -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "$(HOT_PINK) [OK]$(RESET) Full clean done."

re: fclean all

.PHONY: all clean fclean re
