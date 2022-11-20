#include "structs.h"

# define BUFFER_SIZE 1024

void	ft_free_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
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
			return (ft_check_flow(num, *str, minus) - 2);
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
	t_color	color;

	colors = ft_split(str, ',');
	if (!colors)
		ft_error("malloc failed");
	if (ft_strslen(colors) != 3)
		ft_error("wrong input : color must be 3 numbers");
	color = (t_color){ft_atoi(colors[0]), ft_atoi(colors[1]), ft_atoi(colors[2])};
	ft_free_strs(colors);
	if (color.b < 0 || color.b > 255 || color.g < 0 || color.g > 255 || color.r < 0 || color.r > 255)
		ft_error("wrong input : color must be 0 ~ 255");
	return (color);
}

t_pt	get_pt(char *str)
{
	char	**pts;
	t_pt	pt;

	pts = ft_split(str, ',');
	if (!pts)
		ft_error("malloc failed");
	if (ft_strslen(pts) != 3)
		ft_error("wrong input : point must be 3 numbers");
	pt =  ((t_pt){ft_atod(pts[0]), ft_atod(pts[1]), ft_atod(pts[2])});
	ft_free_strs(pts);
	return (pt);
}

t_pt	get_n_vec(char *str)
{
	t_pt	vec;

	vec = get_pt(str);
	if (vec.x < -1 || vec.x > 1 || vec.y < -1 || vec.y > 1 || vec.z < -1 || vec.z > 1)
		ft_error("wrong input : vector must be -1 ~ 1");
	return (vec);
}

void	parse_ambient(char **args, t_info *info)
{
	if (ft_strslen(args) != 3)
		ft_error("wrong input : 'A' must be 3 arguments");
	info->amb.ratio = ft_atod(args[1]);
	if (info->amb.ratio < 0 || info->amb.ratio > 1)
		ft_error("wrong input : ambient ratio must be 0 ~ 1");
	info->amb.color = ft_get_color(args[2]);
}

void	parse_camera(char **args, t_info *info)
{
	if (ft_strslen(args) != 4)
		ft_error("wrong input : 'C' must be 4 arguments");
	info->cam.pos = get_pt(args[1]);
	info->cam.dir = get_pt(args[2]);
	if (info->cam.dir.x < -1 || info->cam.dir.x > 1 || info->cam.dir.y < -1 || info->cam.dir.y > 1 || info->cam.dir.z < -1 || info->cam.dir.z > 1)
		ft_error("wrong input : camera normal vector must be -1 ~ 1");
	info->cam.fov = ft_atod(args[3]);
}

void	parse_light(char **args, t_info *info)
{
	if (ft_strslen(args) != 4)
		ft_error("wrong input : 'L' must be 4 arguments");
	info->light.pos = get_pt(args[1]);
	info->light.ratio = ft_atod(args[2]);
	if (info->light.ratio < 0 || info->light.ratio > 1)
		ft_error("wrong input : light ratio must be 0 ~ 1");
	ft_get_color(args[3]);
}

void	parse_sphere(char **args, t_info *info)
{
	t_obj	*obj;
	t_sp	*new_sp;
	t_list	*new;

	if (ft_strslen(args) != 4)
		ft_error("wrong input : 'sp' must be 4 arguments");
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

	if (ft_strslen(args) != 4)
		ft_error("wrong input : 'pl' must be 4 arguments");
	obj = (t_obj *)malloc(sizeof(t_obj));
	new_pl = (t_pl *)malloc(sizeof(t_pl));
	if (!obj || !new_pl)
		ft_error("malloc failed");
	new_pl->pos = get_pt(args[1]);
	new_pl->dir = get_pt(args[2]);
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

	if (ft_strslen(args) != 6)
		ft_error("wrong input : 'cy' must be 6 arguments");
	obj = (t_obj *)malloc(sizeof(t_obj));
	new_cy = (t_cy *)malloc(sizeof(t_cy));
	if (!obj || !new_cy)
		ft_error("malloc failed");
	new_cy->pos = get_pt(args[1]);
	new_cy->dir = get_pt(args[2]);
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
	if (!ft_strncmp(line, "A ", 2))
		parse_ambient(args, info);
	else if (!ft_strncmp(line, "C ", 2))
		parse_camera(args, info);		
	else if (!ft_strncmp(line, "L ", 2))
		parse_light(args, info);
	else if (!ft_strncmp(line,"sp ", 3))
		parse_sphere(args, info);
	else if (!ft_strncmp(line,"pl ", 3))
		parse_plane(args, info);
	else if (!ft_strncmp(line,"cy ", 3))
		parse_cylinder(args, info);
	else
		ft_error("wrong input : undefined identifier");
	ft_free_strs(args);
}

void	parse_to_info(char *content, t_info *info)
{
	int		i;
	int		flag;
	char	**lines;

	i = -1;
	flag = 0;
	lines = ft_split(content, '\n');
	if (!lines)
		ft_error("malloc failed");
	free(content);
	while (lines[++i])
		parse_a_line(lines[i], &flag, info);
	ft_free_strs(lines);
	if (flag ^ AMB ^ CAM ^ LIGHT)
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
	exceve(&info);
	exit (0);
}
