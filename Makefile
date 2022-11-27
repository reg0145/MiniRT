NAME = miniRT
BONUS = miniRT_bonus
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
		key_move_util.c \
		key_rotate.c \
		key_rotate_util.c \
		hit_plane.c \
		hit_sphere.c \
		hit_cylinder.c \
		reverse_color.c

BONUS_CFILES = main_bonus.c \
		draw_bonus.c \
		vector_util1_bonus.c \
		vector_util2_bonus.c \
		vector_util3_bonus.c \
		parse_file_bonus.c \
		parse_util_bonus.c \
		parse_major_object_bonus.c \
		parse_minor_object_bonus.c \
		init_bonus.c \
		hit_check_bonus.c \
		key_util_bonus.c \
		mouse_click_bonus.c \
		key_move_bonus.c \
		key_move_util_bonus.c \
		key_rotate_bonus.c \
		key_rotate_util_bonus.c \
		hit_plane_bonus.c \
		hit_sphere_bonus.c \
		hit_cylinder_bonus.c \
		reverse_color_bonus.c


SRC_DIR = ./srcs
HDRS = ./headers

SRCS = ${addprefix ${SRC_DIR}/, ${CFILES}}
OBJS = $(SRCS:.c=.o)

BONUS_HDRS = ./headers_bonus
BONUS_SRCS = ${addprefix ${SRC_DIR}_bonus/, ${BONUS_CFILES}}
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g -O2
MLX_FLAGS	=	-L./mlx -lmlx -framework OpenGL -framework Appkit
LIBFT = libft/libft.a
all : $(NAME)

%.o : %.c
	gcc $(CFLAGS) -c -o $@ $< -I $(HDRS) -g

$(BONUS) :$(BONUS_OBJS)
	make -C libft
	make -C mlx
	cc $(CFLAGS) $(BONUS_OBJS) $(LIBFT) $(MLX_FLAGS) -o $(BONUS)

$(NAME) :$(OBJS)
	make -C libft
	make -C mlx
	cc $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

clean :
	make clean -C libft
	make clean -C mlx
	rm -f $(OBJS) $(BONUS_OBJS)

fclean :
	make clean
	rm -f $(LIBFT)
	rm -f $(NAME) $(BONUS)

re : 
	make fclean
	make all

bonus : $(BONUS)
.PHONY : clean fclean re all bonus
