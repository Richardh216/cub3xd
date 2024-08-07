/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoprea <aoprea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:26:46 by rhorvath          #+#    #+#             */
/*   Updated: 2024/07/04 17:06:10 by aoprea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include "../libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# define SPEED 2
# define MAP_X 50
# define MAP_Y 50
# define WIDTH 1920
# define HEIGHT 1080
# define FOV 60

typedef struct f_list
{
	char			*str_buf;
	struct f_list	*next;
}			t_lista;

typedef struct s_pos
{
	int	x;
	int	y;
}		t_pos;

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_ray
{
	t_vec	h;
	t_vec	v;
	double	dir;
	double	dist;
	int		c_dir;
	int		type;
	int		x;
}	t_ray;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir;
}	t_player;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*minimap;
	mlx_image_t		*gun_img;
	mlx_texture_t	*tex[5];
	mlx_texture_t	*gun[15];
	int				top[3];
	int				bottom[3];
	int				c_rgb;
	int				f_rgb;
	char			**map;
	int				map_x;
	int				map_y;
	t_pos			*pos;
	t_player		*player;
}	t_data;

//parse
void	ft_parse(t_data *data, char **argv);
char	*ft_open(int fd);
int		ft_heading(t_data *data, char *str);
void	ft_config(t_data *data, char *str);
void	ft_get_color(t_data *data, char *str);
void	ft_get_color_2(char *top, char *bottom, t_data *data);
char	*ft_extract_color(char *str, int i);
void	ft_heading_2(t_data *data, char *str, int j);
void	ft_get_path(t_data *data, char *str);
void	ft_val_check(t_data *data);
void	check_help(char *str, int i);
void	ft_get_map(t_data *data, char *str, int j);
void	ft_color_help(char *str);
void	ft_get_map_max(t_data *data);
void	ft_map_uniform(t_data *data);

//utils
char	*rspaces(char *str);
int		skip_leading_spaces(char *str, int pos);

//Errors
int		ft_error(char *str, int flag, char *file);
void	path_error(t_data *data, char *str, char *file);
void	free_mat(char **mat);

//get_next_line
char	*get_next_line(int fd);
char	*clean_up_list(t_lista **list);
void	create_list(t_lista **list, int fd);
void	append(t_lista **list, char *buf);
char	*get_line1(t_lista *list);
void	dealloc(int flag, t_lista **list, t_lista *clean_node, char *buf);
void	copy_str(t_lista *list, char *str);
int		len_till_newline(t_lista *list);
t_lista	*find_last_node(t_lista *list);
int		found_newline(t_lista *list);

//render
void	render(t_data *data);
double	rad(double degrees);
int		check_wall(int x, int y, t_data *data);
int		is_solid(char wall);
void	draw_line(t_data *data, int x, int start, int end);
int		reverse_bytes(uint32_t pixel);
void	render_minimap(t_data *data);
void	minimap_show_player(t_data *data);
void	minimap_put_tile(t_data *data, int x, int y, int color);

//player
void	main_loop(void *param);
void	mouse_rotate(t_data *data);
void	check_door_loop(t_data *data, t_vec vec, double *time);
void	check_door(t_data *data);
void	move_back_forth(t_data *data, double speed);
void	move_left_right(t_data *data, double speed);

#endif