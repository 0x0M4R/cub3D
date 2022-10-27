SRCS	= src/cub3d.c src/parse.c

NAME = cub3d
LIBDIR = libft/
LIBFT = libft/libft.a

$(LIBFT):
	make re -C $(LIBDIR)

all:	${NAME}

${NAME}: $(LIBFT)
	gcc -g -Wall -Wextra -Werror ${SRCS} $(LIBFT) -o cub3d
# mlx flags : -Lmlx -lmlx -Linc -framework OpenGL -framework AppKit 

clean:
	rm -f cub3d
	make clean -C $(LIBDIR)

fclean:	clean
	rm -f ${LIBFT}
re:	fclean all