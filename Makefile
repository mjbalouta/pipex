# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/09 16:36:07 by mjoao-fr          #+#    #+#              #
#    Updated: 2025/07/24 18:15:59 by mjoao-fr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I$(LIBFT_DIR) -g
NAME        = pipex
BONUS_NAME	= pipex_bonus
SRCS        = ./src-files/main.c ./src-files/handle_commands.c ./src-files/free_mem.c
BONUS_SRCS  = ./src-bonus-files/main_bonus.c ./src-bonus-files/handle_commands_bonus.c ./src-bonus-files/free_mem_bonus.c
OBJS        = $(SRCS:.c=.o)
BONUS_OBJS  = $(BONUS_SRCS:.c=.o)
LIBFT_DIR   = ./libft-projects
LIBFT       = $(LIBFT_DIR)/complete_libft.a

all: $(LIBFT) $(NAME)

bonus: $(LIBFT) $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	@echo "Compiling bonus..."
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(BONUS_NAME)

$(NAME): $(OBJS)
	@echo "Compiling..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Removing objects..."
	@$(MAKE) clean -C $(LIBFT_DIR) > /dev/null
	@rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	@echo "Removing executable..."
	@$(MAKE) fclean -C $(LIBFT_DIR) > /dev/null
	@rm -f $(NAME)

tester:
	@echo "  $(B)$(AQUA)TESTER$(D)"
	@if [ ! -d "tester" ]; then \
		echo "   $(B)$(GOLD)Cloning visualizer repository$(D) 💾💾"; \
		git clone git@github.com:michmos/42_pipex_tester.git tester; \
		cd tester && bash run.sh --show-valgrind; \
	else \
		cd tester && bash run.sh --show-valgrind; \
	fi

re: fclean all

.PHONY: all clean fclean re bonus tester