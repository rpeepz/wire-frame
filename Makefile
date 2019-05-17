# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/09 00:09:32 by rpapagna          #+#    #+#              #
#    Updated: 2019/05/16 22:55:16 by rpapagna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fdf

#COLORS
GREEN	= \033[0;32m
RED		= \033[0;31m
NC		= \033[0m

SRC		= image.c\
		inputs.c\
		lines.c\
		list_ops.c\
		main.c\
		map.c\
		parse.c\
		window.c

FLAGS	= -Wall -Wextra -Werror
INC		= -I includes/fdf.h

#MLX COMPILE ORDER
MLX_LNK	= -L ./minilibx_macros -l mlx_macros -framework OpenGL -framework AppKit
#LIB COMPILE ORDER
FT_LNK	= -L ./libft -l ft

all:	$(NAME)

$(NAME):
		@printf "[$(GREEN)f.d.f.$(NC)]\t\t[:          :]\r"	#PRINT
		@make -C libft
		@printf "[$(GREEN)f.d.f.$(NC)]\t\t[:##########:]\r"	#PRINT
		@make -C minilibx_macros
		@printf "[$(GREEN)f.d.f.$(NC)]\t\t[:#######   :]\r" #PRINT
		@gcc $(FLAGS) $(addprefix src/,$(SRC)) $(INC) $(MLX_LNK) $(FT_LNK) -o $(NAME)
		@printf "[$(GREEN)f.d.f.$(NC)]\t\t[:########  :]\r" #PRINT
		@printf "[$(GREEN)f.d.f.$(NC)]\t\t[:##########:]\n"	#PRINT

debug:
		@gcc $(FLAGS) -g $(addprefix src/,$(SRC)) $(MLX_LNK) $(FT_LNK) $(INC) -o $(NAME) -fsanitize=address
		@printf "[$(GREEN)debug.$(NC)]\t\t[$(RED):##########:$(NC)]\n"	#PRINT
1mo:
		@printf "[$(RED)f.d.f.$(NC)]\t\t[:#         :]\r"	#PRINT
		@rm -rf $(NAME).dSYM
		@printf "[$(RED)f.d.f.$(NC)]\t\t[:###       :]\r"	#PRINT
		@rm -rf $(NAME)
		@printf "[$(GREEN)f.d.f.$(NC)]\t\t[:#####     :]\r"	#PRINT
		@gcc -w $(FLAGS) $(addprefix src/,$(SRC)) $(INC) $(MLX_LNK) $(FT_LNK) -o $(NAME)
		@printf "[$(GREEN)f.d.f.$(NC)]\t\t[:#######   :]\r"	#PRINT
		@printf "[$(GREEN)f.d.f.$(NC)]\t\t[:##########:]\n"	#PRINT
clean:
		@printf "[$(RED)remove$(NC)]\t\t[:          :]\r"	#PRINT
		@make -C libft clean
		@printf "[$(RED)remove$(NC)]\t\t[:##########:]\r"	#PRINT
		@make -C minilibx clean
		@printf "[$(RED)remove$(NC)]\t\t[:#######   :]\r"	#PRINT
		@make -C minilibx_macros clean
		@printf "[$(RED)remove$(NC)]\t\t[:##########:]\n"	#PRINT

fclean: clean
		@make -C libft fclean
		@printf "[$(RED)remove$(NC)]\t\t[:#######   :]\r"	#PRINT
		@rm -rf $(NAME)
		@printf "[$(RED)remove$(NC)]\t\t[:########  :]\r"	#PRINT
		@rm -rf $(NAME).dSYM
		@printf "[$(RED)remove$(NC)]\t\t[:##########:]\n"	#PRINT

re: fclean all

.PHONY:	all clean fclean re debug
