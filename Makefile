# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/09 16:36:07 by mjoao-fr          #+#    #+#              #
#    Updated: 2025/07/29 14:46:32 by mjoao-fr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS      = -Wall -Wextra -Werror -I$(LIBFT_DIR) -g
NAME        = pipex

SRCS        = ./src-files/main.c ./src-files/handle_commands.c ./src-files/free_mem.c
BONUS_SRCS  = ./src-bonus-files/main_bonus.c ./src-bonus-files/handle_commands_bonus.c ./src-bonus-files/mem_handling_bonus.c ./src-bonus-files/bonus_utils.c

OBJS        = $(SRCS:.c=.o)
BONUS_OBJS  = $(BONUS_SRCS:.c=.o)

LIBFT_DIR   = ./libft-projects
LIBFT       = $(LIBFT_DIR)/complete_libft.a

all: $(LIBFT) $(NAME)

bonus: $(LIBFT) $(BONUS_OBJS)
	@if [ -f $(NAME) ]; then \
	echo "Executable already exists. No relink."; \
	else \
	echo "Compiling pipex bonus..."; \
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(NAME); fi

$(NAME): $(OBJS)
	@echo "Compiling pipex..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning object files..."
	@$(MAKE) clean -C $(LIBFT_DIR) > /dev/null
	@rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	@echo "Removing executable..."
	@$(MAKE) fclean -C $(LIBFT_DIR) > /dev/null
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
