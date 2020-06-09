/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getinfo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuarez- <msuarez-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 15:23:15 by msuarez-          #+#    #+#             */
/*   Updated: 2020/06/09 15:42:39 by msuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		exit_error(int n)
{
	if (n == 1)
		ft_putendl("Invalid map! Check the number of rows/cols are the same.");
	else if (n == 2)
		ft_putendl("Invalid map! The character needs a place to stand on.");
	else if (n == 3)
		ft_putendl("Invalid map! It's mandatory to have walls on map limits.");
	ft_putendl("This is the smallest possible map:");
	ft_putendl("1 1 1\n1 0 1\n1 1 1");
	exit(0);
}

static int	count_words(const char *line)
{
	int		char_count;
	int		i;
	int		len;
	int		num_count;
	char	last_char;

	i = 0;
	char_count = 0;
	num_count = 0;
	len = ft_strlen(line);
	if (len > 0)
		last_char = line[0];
	while (i <= len)
	{
		if ((line[i] == ' ' || line[i] == '\0') && last_char != ' ')
			char_count++;
		if (ft_isdigit(line[i]))
			num_count++;
		last_char = line[i];
		i++;
	}
	if (num_count == 0 || char_count != num_count)
		exit_error(1);
	return (char_count);
}

int			get_height(char *filepath)
{
	int		fd;
	int		ret;
	char	*line;

	fd = open(filepath, O_RDONLY);
	ret = 0;
	while (get_next_line(fd, &line) > 0)
	{
		ret++;
		free(line);
		line = 0;
	}
	if (ret == 0)
	{
		printf("Error: No height, empty map?\n");
		exit(0);
	}
	close(fd);
	return (ret);
}

int			get_width(char *filepath)
{
	int		fd;
	int		ret;
	char	*line;

	fd = open(filepath, O_RDONLY);
	ret = 0;
	get_next_line(fd, &line);
	ret = count_words(line);
	free(line);
	line = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (count_words(line) != ret)
			exit_error(1);
		free(line);
		line = 0;
	}
	if (ret == 0)
	{
		printf("Error: No width, empty map?\n");
		exit(0);
	}
	close(fd);
	return (ret);
}
