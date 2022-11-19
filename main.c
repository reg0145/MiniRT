#include "libft/headers/libft.h"
#include "structs.h"
#include <sys/fcntl.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

# define BUFFER_SIZE 1024

void	ft_error(char *msg)
{
	ft_putendl_fd("error", 2);
	ft_putendl_fd(msg, 2);
	exit(1);
}

void	check_file_extension(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 3 || ft_strcmp(&file[len - 3], ".rt"))
		ft_error("wrong file extension");
}

void	read_file(char *file, char **content)
{
	int		fd;
	int		read_size;
	char	buf[BUFFER_SIZE];
	char	*tmp;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error("can't open file");
	while (1)
	{
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size < 0)
			break ;
		tmp = *content;
		*content = ft_strjoin(*content, buf);
		free(tmp);
		if (!content)
			ft_error("malloc failed");
		if (read_size < BUFFER_SIZE)
			break ;
	}
}

void	check_duplicate_info(char key, int *flag)
{
	if (key == 'A' && *flag & AMB)
		ft_error("'A' can be only one");
	if (key == 'C' && *flag & CAM)
		ft_error("'C' can be only one");
	if (key == 'L' && *flag & LIGHT)
		ft_error("'L' can be only one");
	if (key == 'A')
		*flag |= AMB;
	if (key == 'C')
		*flag |= CAM;
	if (key == 'L')
		*flag |= LIGHT;
}

static int	ft_check_flow(double num, int c, int minus)
{
	num *= minus;
	c -= '0';
	if (minus == 1)
		if (num * 10 + c < num)
			return (1);
	if (minus == -1)
		if (num * 10 - c > num)
			return (2);
	return (0);
}

static void	check_minus_and_format(char **str, int *minus)
{
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			*minus *= (-1);
		(*str)++;
	}
	if (!ft_isdigit(**str))
		ft_error("worng input : type must be double");
}



double	ft_atod(char *str)
{
	double			num;
	int				minus;
	double			result;

	num = 0;
	result = 0;
	minus = 1;
	check_minus_and_format(&str, &minus);
	while (ft_isdigit(*str) && *str)
	{
		if (ft_check_flow(num, *str, minus))
			ft_error("worng input : type should be double");
		num *= 10;
		num += *str - '0';
		str++;
	}
	if (*str && *(str++) != '.')
		ft_error("worng input : type should be number");
	result = (double)(num * minus);
	num = 10;
	while (ft_isdigit(*str) && *str)
	{
		result += (*str - '0') / num;
		num *= 10;
		str++;
	}
	if (*str && !ft_isdigit(*str))
		ft_error("worng input : type should be number");
	return (result);
}

t_color	ft_get_color(char *str)
{
	char	**colors;

	colors = ft_split(str, ',');
	if (!colors)
		ft_error("malloc failed");
	if (ft_strslen(colors) != 3)
		ft_error("wrong input : color must be 3 numbers");
	return ((t_color){ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2])});
}

t_pt	get_pt(char *str)
{
	char	**pts;

	pts = ft_split(str, ',');
	if (!pts)
		ft_error("malloc failed");
	if (ft_strslen(pts) != 3)
		ft_error("wrong input : point must be 3 numbers");
	return ((t_pt){ft_atod(pts[0]), ft_atod(pts[1]), ft_atod(pts[2])});
}

void	parse_ambient(char **args, t_info *info)
{
	info->amb.ratio = ft_atod(args[1]);
	info->amb.color = ft_get_color(args[2]);
}

void	parse_camera(char **args, t_info *info)
{
	info->cam.pos = get_pt(args[1]);
	info->cam.n_vec = get_pt(args[2]);
	info->cam.fov = ft_atod(args[3]);
}

void	parse_light(char **args, t_info *info)
{
	info->light.pos = get_pt(args[1]);
	info->light.ratio = ft_atod(args[2]);
	ft_get_color(args[3]);
}

void	parse_sphere(char **args, t_info *info)
{
	t_obj	*obj;
	t_sp	*new_sp;
	t_list	*new;

	obj = (t_obj *)malloc(sizeof(t_obj));
	new_sp = (t_sp *)malloc(sizeof(t_sp));
	if (!obj || !new_sp)
		ft_error("malloc failed");
	new_sp->pos = get_pt(args[1]);
	new_sp->r = ft_atod(args[2]);
	new_sp->color = ft_get_color(args[3]);
	obj->type = SPHERE;
	obj->obj = new_sp;
	new = ft_lstnew(obj);
	if (!new)
		ft_error("malloc failed");
	ft_lstadd_back(&info->objs, new);
}

void	parse_plane(char **args, t_info *info)
{
	t_obj	*obj;
	t_pl	*new_pl;
	t_list	*new;

	obj = (t_obj *)malloc(sizeof(t_obj));
	new_pl = (t_pl *)malloc(sizeof(t_pl));
	if (!obj || !new_pl)
		ft_error("malloc failed");
	new_pl->pos = get_pt(args[1]);
	new_pl->n_vec = get_pt(args[2]);
	new_pl->color = ft_get_color(args[3]);
	obj->type = PLANE;
	obj->obj = new_pl;
	new = ft_lstnew(obj);
	if (!new)
		ft_error("malloc failed");
	ft_lstadd_back(&info->objs, new);
}

void	parse_cylinder(char **args, t_info *info)
{
	t_obj	*obj;
	t_cy	*new_cy;
	t_list	*new;

	obj = (t_obj *)malloc(sizeof(t_obj));
	new_cy = (t_cy *)malloc(sizeof(t_cy));
	if (!obj || !new_cy)
		ft_error("malloc failed");
	new_cy->pos = get_pt(args[1]);
	new_cy->n_vec = get_pt(args[2]);
	new_cy->r = ft_atod(args[3]);
	new_cy->height = ft_atod(args[4]);
	new_cy->color = ft_get_color(args[5]);
	obj->type = CYLINDER;
	obj->obj = new_cy;
	new = ft_lstnew(obj);
	if (!new)
		ft_error("malloc failed");
	ft_lstadd_back(&info->objs, new);
}

void	parse_a_line(char *line, int *flag, t_info *info)
{
	char	**args;

	args = ft_split(line, ' ');
	if (!args)
		ft_error("malloc failed");
	check_duplicate_info(*line, flag);
	if (*line == 'A')
		parse_ambient(args, info);
	else if (*line == 'C')
		parse_camera(args, info);		
	else if (*line == 'L')
		parse_light(args, info);
	else if (!ft_strncmp(line,"sp ", 3))
		parse_sphere(args, info);
	else if (!ft_strncmp(line,"pl ", 3))
		parse_plane(args, info);
	else if (!ft_strncmp(line,"cy ", 3))
		parse_cylinder(args, info);
	else
		ft_error("wrong input : undefined identifier");
}

void	parse_to_info(char *content, t_info *info)
{
	int		i;
	int		flag;
	char	**lines;

	lines = ft_split(content, '\n');
	if (!lines)
		ft_error("malloc failed");
	i = -1;
	flag = 0;
	while (lines[++i])
	{
		parse_a_line(lines[i], &flag, info);
		free(lines[i]);
	}
	free(lines);
	if (!(flag ^ AMB) || !(flag ^ CAM) || !(flag ^ LIGHT))
		ft_error("no essential identifier(A, C, L)");
}

void	parse(char *av, t_info *info)
{
	char	*content;

	content = ft_strdup("");
	if (!content)
		ft_error("malloc failed");
	check_file_extension(av);
	read_file(av, &content);
	parse_to_info(content, info);
}

int	main(int ac, char **av)
{
	t_info	info;

	ft_memset(&info, 0, sizeof(t_info));
	if (ac != 2)
		ft_error("wrong number of arguments");
	parse(av[1], &info);
	return (0);
}