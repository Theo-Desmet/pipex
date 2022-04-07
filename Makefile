NAME = pipex

SRC =	./src/main.c\
	./src/child.c\
	./src/error.c\
	./src/free.c\

LIB_PATH = libft/

CC = @clang

CFLAGS = -g -Wall -Werror -Wextra

OBJ = $(SRC:.c=.o)

%.o:%.c pipex.h
	@$(CC) -o $@ -c $< $(CFLAGS)

all: $(NAME)

$(NAME): begin $(OBJ)
	@$(MAKE) -s all -C libft
	@$(CC) $(OBJ) $(LIB_PATH)libft.a -o $(NAME)
	@echo "\033[106;32mcompilation de pipex terminées\033[0m"	

clean:
	@make -C $(LIB_PATH) fclean
	@rm -f $(OBJ)
	@echo "\033[101;30msuppression des fichier *.o de pipex\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[101;30msuppression de l'executable pipex\033[0m"

re: fclean all

begin:
	@echo "\033[106;35mdebut de la compilation de pipex\033[0m"

.PHONY: all clean fclean re

