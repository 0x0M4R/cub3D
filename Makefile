NAME			=		cub3d

SRCS_DIR		=		./srcs/

SRCS			=		cub3d.c				\
						parser.c			\
						map.c				\
						get_elements.c		\
						engine.c			\
						utils.c				\
						big_brain.c			\
						raycasting_utils.c	\
						render.c			\
						player.c			\
						tmp.c				\
						map_utils.c			\
						assets.c			\

OBJS			=		$(addprefix $(SRCS_DIR),$(SRCS:.c=.o))

LIBDIR			=		libft/

LIBFT			=		libft/libft.a

CC				=		gcc

CFLAGS			=		-Wall -Werror -Wextra -Iinc -g

DEBUG			=		-g -DDEBUG

RM				=		rm -f

UNAME			:=		$(shell uname)

DBG				=		0

ifeq ($(DBG), 1)
	CFLAGS += $(DEBUG)
endif

ifeq ($(UNAME),Linux)
MLX_DIR			=		./mlx_linux
MLX_FLAGS		=		 -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz 
%.o				:		 %.c
						$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -I./inc -c $< -o $@
else
MLX_DIR			=		./mlx
MLX_FLAGS		=		-Lmlx -lmlx -framework OpenGL -framework AppKit -Ofast
%.o				: 		%.c
						$(CC) $(CFLAGS) -Imlx  -c $< -o $@
endif

$(NAME)			:		$(OBJS)
						make -C $(LIBDIR)
						$(CC) $(CFLAGS) $(LIBFT) $(OBJS) $(MLX_FLAGS) -o $(NAME)

all				:		$(NAME)

clean			:
						$(RM) $(OBJS)
						make clean -C $(LIBDIR)

fclean			:		clean
						make fclean -C $(LIBDIR)
						$(RM) $(NAME)

re				:		fclean all