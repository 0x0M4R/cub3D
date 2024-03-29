  NAME			=		cub3d

SRCS_DIR		=		./srcs/

SRCS			=		cub3d.c				\
						parser.c			\
						read_map.c			\
						map_utils.c			\
						map.c				\
						get_elements.c		\
						engine.c			\
						utils.c				\
						big_brain.c			\
						rays_utils.c		\
						raycasting_utils.c	\
						render.c			\
						player.c			\
						assets.c			\
						memory.c			\
						minimap.c			\
						doors.c				\
						collision.c			\
						# tmp.c				\

OBJS			=		$(addprefix $(SRCS_DIR),$(SRCS:.c=.o))

LIBDIR			=		libft/

LIBFT			=		libft/libft.a

CC				=		gcc

CFLAGS			=		-Wall -Werror -Wextra -Iinc -g

RM				=		rm -f

UNAME			:=		$(shell uname)

DBG				=		0

ifeq ($(UNAME),Linux)
MLX_DIR			=		./mlx_linux
MLX_FLAGS		=		 -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz 
%.o				:		 %.c
						$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -c $< -o $@
else
MLX_DIR			=		./mlx
MLX_FLAGS		=		-Lmlx -lmlx -framework OpenGL -framework AppKit -Ofast
%.o				: 		%.c
						$(CC) $(CFLAGS) -Imlx  -c $< -o $@
endif

$(NAME)			:		$(OBJS)
						make -C $(LIBDIR) 
						make -C $(MLX_DIR)
						$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) $(LIBFT) -o $(NAME)

all				:		$(NAME)

clean			:
						$(RM) $(OBJS)
						make clean -C $(LIBDIR)
						make clean -C $(MLX_DIR)

fclean			:		clean
						make fclean -C $(LIBDIR)
						$(RM) $(NAME)

re				:		fclean all
