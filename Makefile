NAME			=		cub3d

SRCS_DIR		=		./srcs/

SRCS			=		cub3d.c				\
						parse.c				\
						parse_elements.c	\

OBJS			=		$(addprefix $(SRCS_DIR),$(SRCS:.c=.o))

LIBDIR			=		libft/

LIBFT			=		libft/libft.a

CC				=		gcc

CFLAGS			=		-Wall -Werror -Wextra -g

RM				=		rm -f

UNAME			:=		$(shell uname)

ifeq ($(UNAME),Linux)
MLX_DIR			=		./mlx_linux
MLX_FLAGS		=		 -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz 
%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@
else
MLX_DIR			=		./mlx
MLX_FLAGS		=		-Lmlx -lmlx -framework OpenGL -framework AppKit -Ofast
%.o				: 		%.c
						$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@
endif

$(NAME)			:		$(OBJS)
						make -C $(LIBDIR)
						$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) $(LIBFT) -o $(NAME) -I inc

all				:		$(NAME)

clean			:
						$(RM) $(OBJS)
						make clean -C $(LIBDIR)

fclean			:		clean
						make fclean -C $(LIBDIR)
						$(RM) $(NAME)

re				:		fclean all