#
#
RED		= \033[0;31m
NC		= \033[0m
NOM=libmlx_macros.a
SRC= mlx_shaders.c mlx_xpm.c mlx_int_str_to_wordtab.c
SRM= mlx_new_window.m mlx_init_loop.m mlx_new_image.m
#OBJ1=$(SRC:.c=.o)
#OBJ=$(OBJ1:.m=.o)
OBJ = $(patsubst %.c,%.o,$(SRC))
OBJ += $(patsubst %.m,%.o,$(SRM))
CFLAGS+=-O2

all: $(NOM)

$(NOM):
	@cc -w $(CFLAGS) -c $(SRC)
	@printf "[$(GREEN)create$(NC)]\t\t[:#####     :]\r"
	@cc -w $(CFLAGS) -c $(SRM)
	@printf "[$(GREEN)create$(NC)]\t\t[:######    :]\r"
	@ar -rcs $(NOM) $(OBJ)
#$(NOM):	$(OBJ)
#	@ar -rc $(NOM) $(OBJ)
#	@ranlib $(NOM)

clean:
	@rm -f $(NOM) $(OBJ) *~
	@rm -f mlx_app
	@printf "[$(RED)remove$(NC)]\t\t[:##########:]\n"

re: clean all
