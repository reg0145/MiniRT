NAME = miniRT
SRCS = main.c

HDRS = headers

OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit
LIBFT = libft/libft.a
all : $(NAME)

%.o : %.c
	gcc $(CFLAGS) -c -o $@ $< -I $(HDRS)

$(NAME) :$(OBJS)
	make -C libft
	make -C mlx
	cc $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

clean :
	make clean -C libft
	make clean -C mlx
	rm -f $(OBJS) $(BNSO)

fclean : clean
	rm -f $(LIBFT)
	rm -f $(NAME)

re : 
	fclean
	all

.PHONY : clean fclean re all
