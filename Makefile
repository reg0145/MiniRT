NAME = miniRT
CFILES = main.c \
		draw.c \
		vector_util1.c \
		vector_util2.c \
		vector_util3.c \
		parse_file.c \
		parse_util.c \
		parse_major_object.c \
		parse_minor_object.c \
		init.c \
		hit_check.c \
		key_util.c \
		mouse_click.c \
		key_move.c \
		key_rotate_and_util.c \
		hit_plane.c \
		hit_sphere.c \
		hit_cylinder.c

SRC_DIR = ./srcs
HDRS = ./headers

SRCS = ${addprefix ${SRC_DIR}/, ${CFILES}}

OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g -O3
MLX_FLAGS	=	-L./mlx -lmlx -framework OpenGL -framework Appkit
LIBFT = libft/libft.a
all : $(NAME)

%.o : %.c
	gcc $(CFLAGS) -c -o $@ $< -I $(HDRS) -g

$(NAME) :$(OBJS)
	make -C libft
	make -C mlx
	cc $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

clean :
	make clean -C libft
	make clean -C mlx
	rm -f $(OBJS) $(BNSO)

fclean :
	make clean
	rm -f $(LIBFT)
	rm -f $(NAME)

re : 
	make fclean
	make all

.PHONY : clean fclean re all
