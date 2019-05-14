# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/09 00:09:32 by rpapagna          #+#    #+#              #
#    Updated: 2019/05/14 16:08:14 by rpapagna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fdf

GREEN	= \033[0;32m

RED		= \033[0;31m
NC		= \033[0m

SRC		= errors.c\
		image.c\
		list_ops.c\
		main.c\
		map.c\
		parse.c\
		window.c

FLAGS	= -Wall -Wextra -Werror
MLX_LNK	= -L ./minilibx_macros -l mlx_macros -framework OpenGL -framework AppKit
FT_LNK	= -L ./libft -l ft
INC		= -I includes/fdf.h

all:	$(NAME)

$(NAME):
		@printf "[$(GREEN)f.d.f.$(NC)]\t\t[:          :]\r"
		@make -C libft
		@printf "[$(GREEN)f.d.f.$(NC)]\t\t[:##########:]\r"
		@make -C minilibx_macros
		@printf "[$(GREEN)f.d.f.$(NC)]\t\t[:#######   :]\r"
		@gcc $(FLAGS) $(addprefix src/,$(SRC)) $(INC) $(MLX_LNK) $(FT_LNK) -o $(NAME)
		@printf "[$(GREEN)f.d.f.$(NC)]\t\t[:########  :]\r"
		@printf "[$(GREEN)f.d.f.$(NC)]\t\t[:##########:]\n"

debug:
		@gcc $(FLAGS) -g $(addprefix src/,$(SRC)) $(MLX_LNK) $(FT_LNK) $(INC) -o $(NAME)
		@printf "[$(GREEN)debug.$(NC)]\t\t[$(RED):##########:$(NC)]\n"
1mo:
		@gcc $(FLAGS) $(addprefix src/,$(SRC)) $(INC) $(MLX_LNK) $(FT_LNK) -o $(NAME)
clean:
		@printf "[$(RED)remove$(NC)]\t\t[:          :]\r"
		@make -C libft clean
		@printf "[$(RED)remove$(NC)]\t\t[:##########:]\r"
		@make -C minilibx clean
		@printf "[$(RED)remove$(NC)]\t\t[:#######   :]\r"
		@make -C minilibx_macros clean
		@printf "[$(RED)remove$(NC)]\t\t[:##########:]\n"

fclean: clean
		@make -C libft fclean
		@printf "[$(RED)remove$(NC)]\t\t[:#######   :]\r"
		@rm -rf $(NAME)
		@printf "[$(RED)remove$(NC)]\t\t[:########  :]\r"
		@rm -rf $(NAME).dSYM
		@printf "[$(RED)remove$(NC)]\t\t[:##########:]\n"

re: fclean all

.PHONY:	all clean fclean re debug
