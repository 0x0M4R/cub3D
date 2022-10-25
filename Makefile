SRCS	= src/cub3d.c src/get_next_line.c src/get_next_line_utils.c src/parse.c

NAME = cub3d

all:	${NAME}

${NAME}:
	gcc -Wall -Wextra -Werror ${SRCS} -o cub3d 
# mlx flags : -Lmlx -lmlx -Linc -framework OpenGL -framework AppKit 

clean:
	rm -f cub3d

fclean:	clean

re:	fclean all