/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:56:02 by nheo              #+#    #+#             */
/*   Updated: 2022/11/21 14:52:13 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <fcntl.h>

#define BUFFER_SIZE 1024

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
		ft_memset(buf, 0, BUFFER_SIZE);
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

static void	check_duplicate_info(char key, int *flag)
{
	if (key == 'A' && *flag & AMB)
		ft_error("'A' can be only one");
	if (key == 'C' && *flag & CAM)
		ft_error("'C' can be only one");
	if (key == 'L' && *flag & LIT)
		ft_error("'L' can be only one");
	if (key == 'A')
		*flag |= AMB;
	if (key == 'C')
		*flag |= CAM;
	if (key == 'L')
		*flag |= LIT;
}

static void	parse_a_line(char *line, int *flag, t_info *info)
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
	else if (!ft_strncmp(line, "sp ", 3))
		parse_sphere(args, info);
	else if (!ft_strncmp(line, "pl ", 3))
		parse_plane(args, info);
	else if (!ft_strncmp(line, "cy ", 3))
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
	if (flag ^ AMB ^ CAM ^ LIT)
		ft_error("no essential identifier(A, C, L)");
}
