# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpapagna <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/09 00:09:32 by rpapagna          #+#    #+#              #
#    Updated: 2019/05/09 02:14:28 by rpapagna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fdf
GREEN	= \033[0;32m
RED		= \033[0;31m
NC		= \033[0m
FLAGS	= -Wall -Wextra -Werror
LIB		= libft/libft.a
LIBX	= libmlx/libmlx.a
SRC		= main.c

all:	$(NAME)

$(NAME):
		@printf "[$(GREEN)f.d.f.$(NAME):$(NC)]\t\t[$(RED):#   :$(NC)]\r"
		@make -C libft
		@gcc $(FLAGS) $(addprefix src/,$(SRCS)) $(LIB) $(LIBX) -o $(NAME)
		@printf "[$(GREEN)f.d.f.:$(NC)]\t\t[$(RED):####:$(NC)]\r"

debug:
		@printf "[$(GREEN)debug.$(NC)]\t\t[$(RED):#   :$(NC)]\r"
		@gcc $(FLAGS) -g $(LIB) $(LIBX) -o $(NAME)
		@printf "[$(GREEN)debug.$(NC)]\t\t[$(RED):####:$(NC)]\r"

clean:
		@printf "[$(GREEN)remove$(NC)]\t\t[$(RED):#    :$(NC)]\r"
		@make -C libft clean
		@printf "[$(GREEN)remove$(NC)]\t\t[$(RED):####:$(NC)]\r"

fclean:
		@printf "[$(GREEN)remove$(NC)]\t\t[$(RED):#    :$(NC)"
		@rm -rf $(NAME)
		@printf "[$(GREEN)remove$(NC)]\t\t[$(RED):##   :$(NC)]\r"
		@make -C libft fclean
		@printf "[$(GREEN)remove$(NC)]\t\t[$(RED):####:$(NC)]\r"

re: fclean all

.PHONY:	all clean fclean re debug
