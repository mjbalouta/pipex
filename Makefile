# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/09 16:36:07 by mjoao-fr          #+#    #+#              #
#    Updated: 2025/07/31 12:47:08 by mjoao-fr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS      = -Wall -Wextra -Werror -I$(LIBFT_DIR) -g
NAME        = pipex

SRCS        = ./src-files/main.c ./src-files/handle_commands.c ./src-files/mem_handling.c ./src-files/utils.c
BONUS_SRCS  = ./src-bonus-files/main_bonus.c ./src-bonus-files/handle_commands_bonus.c ./src-bonus-files/mem_handling_bonus.c ./src-bonus-files/bonus_utils.c

OBJS        = $(SRCS:.c=.o)
BONUS_OBJS  = $(BONUS_SRCS:.c=.o)

LIBFT_DIR   = ./libft-projects
LIBFT       = $(LIBFT_DIR)/complete_libft.a

all: $(LIBFT) $(NAME)

bonus: $(LIBFT) $(BONUS_OBJS)
	@if [ -f $(NAME) ]; then \
	echo "Executable already exists. Please do 'make fclean'."; \
	else \
	echo "Compiling pipex bonus..."; \
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(NAME); fi

$(NAME): $(OBJS)
	@echo "Pipex compiled."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Object files cleaned."
	@$(MAKE) clean -C $(LIBFT_DIR) > /dev/null
	@rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	@echo "Executable removed."
	@$(MAKE) fclean -C $(LIBFT_DIR) > /dev/null
	@rm -f $(NAME)

re: fclean all

tester:
	@echo "  $(B)$(AQUA)TESTER$(D)"
	@if [ ! -d "tester" ]; then \
		echo "   $(B)$(GOLD)Cloning visualizer repository$(D) 💾💾"; \
		git clone git@github.com:michmos/42_pipex_tester.git tester; \
		cd tester && bash run.sh --show-valgrind; \
	else \
		cd tester && bash run.sh --show-valgrind; \
	fi

.PHONY: all clean fclean re bonus
