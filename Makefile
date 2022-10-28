SRCS	= src/cub3d.c src/parse.c src/parse_elements.c

NAME = cub3d
LIBDIR = libft/
LIBFT = libft/libft.a
MLXDIR = mlx/
MLX = mlx/libmlx.a


$(MLX):
	make all -C $(MLXDIR)
$(LIBFT):
	make all -C $(LIBDIR)

all:	${NAME}

${NAME}: $(MLX) $(LIBFT) 
	gcc -g -Wall -Wextra -Werror -Lmlx -lmlx -Linc -framework OpenGL -framework AppKit ${SRCS} $(LIBFT) -o cub3d
# mlx flags : -Lmlx -lmlx -framework OpenGL -framework AppKit 

clean:
	rm -f cub3d
	
	make clean -C $(LIBDIR)

fclean:	clean
	rm -f ${LIBFT}
re:	fclean all