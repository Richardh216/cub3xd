/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:12:39 by rhorvath          #+#    #+#             */
/*   Updated: 2024/07/05 13:03:20 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_heading_2(t_data *data, char *str, int j)
{
	int		i;

	i = j;
	while (str[i] && (str[i] == ' ' || str[i] == '\n'))
	{
		if (str[i] == '\n')
			j = i;
		i++;
	}
	ft_get_map(data, str, j);
}

int	ft_heading(t_data *data, char *str)
{
	int		i;
	int		j;
	char	*ptr[6];

	i = 0;
	j = 0;
	while (str[i] && j < 6)
	{
		if (!ft_strncmp(str + i, "NO", 2) || !ft_strncmp(str + i, "SO", 2)
			|| !ft_strncmp(str + i, "WE", 2) || !ft_strncmp(str + i, "EA", 2)
			|| !ft_strncmp(str + i, "C", 1) || !ft_strncmp(str + i, "F", 1))
		{
			ptr[j++] = str + i;
			while (str[i] && str[i] != '\n')
				i++;
			str[i] = '\0';
		}
		else if (str[i] != ' ' && str[i] != '\n')
			ft_error("Invalid configuration!", 1, NULL);
		i++;
	}
	while (j > 0)
		ft_config(data, ptr[--j]);
	free(str);
	return (i);
}

static void	init_data(t_data *data)
{
	int	i;

	i = -1;
	data->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->map = NULL;
	data->map_x = -1;
	data->map_y = -1;
	data->pos = malloc(sizeof(t_pos));
	if (!data->pos)
		ft_error("Malloc error!", 1, NULL);
	data->pos->x = -1;
	data->pos->y = -1;
	while (++i < 4)
		data->tex[i] = NULL;
	i = -1;
	while (++i < 3)
	{
		data->top[i] = -1;
		data->bottom[i] = -1;
	}
}

char	*ft_open(int fd)
{
	char	*tmp;
	char	*line;
	char	*temp;

	line = ft_strdup("");
	if (!line)
	{
		close(fd);
		ft_error("Malloc error!", 1, NULL);
	}
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		temp = line;
		line = ft_strjoin(temp, tmp);
		free(tmp);
		free(temp);
	}
	close(fd);
	return (line);
}

void	ft_parse(t_data *data, char **argv)
{
	int		i;
	int		fd;
	char	*tmp;
	char	*temp;

	i = ft_strlen(argv[1]);
	if (i < 4)
		ft_error("Incorrect file name!", 1, NULL);
	if (ft_strncmp(&argv[1][i - 4], ".cub", 4))
		ft_error("Incorrect file format!", 1, NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error("Could not open file!", 1, NULL);
	tmp = ft_open(fd);
	init_data(data);
	temp = ft_strdup(tmp);
	i = ft_heading(data, temp);
	ft_val_check(data);
	ft_heading_2(data, tmp, i);
}
