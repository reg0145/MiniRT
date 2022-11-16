#include "structs.h"
#include <sys/fcntl.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

# define BUFFER_SIZE 1024

void	check_file_extension(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 3 || !ft_strcmp(&file[len - 3]), ".rt")
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

void parse_ambient(char **args, t_info *info)
{
	
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
	if (*line == 'C')
		parse_camera(args, info);		
	if (*line == 'L')
		parse_light(args, info);
	if (*line == 'sp')
		parse_sphere(args, info);
	if (*line == 'pl')
		parse_plane(args, info);
	if (*line == 'cy')
		parse_cylinder(args, info);
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
	if (flag ^ AMB || flag ^ CAM || flag ^ LIGHT)
		ft_error("no essential identifier(A, C, L)");
}

void	parse(char *av, t_info *info)
{
	char	*content;

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

}