/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 17:33:18 by jemartel          #+#    #+#             */
/*   Updated: 2022/06/09 16:17:58 by jemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  CUBE_H
# define  CUBE_H
# define TWO_PI			6.28318530
# define PI				3.14159265359
# define HEIGHT			600
# define WIDTH			800

# include "stdio.h"
# include "stdlib.h"
# include "../utils/get_next_line.h"
# include "../utils/libft/libft.h"
# include "../utils/MLX/include/MLX42/MLX42.h"
# include "stdbool.h"
# include "math.h"

typedef struct t_dlist
{
	void			*content;
	struct t_dlist	*next;
	struct t_dlist	*prev;
}					t_dlist;

typedef struct t_ray
{
	double			dx;
	double			dy;
	double			angle;
	double			pos_rayx;
	double			pos_rayy;
	int				map_rayx;
	int				map_rayy;
	double			nb_step_x;
	double			nb_step_y;
	double			len;
	char			last_hit;
	int				max_len;
	int				last_cordy;
	int				last_cordx;
	int				map_heigth;
}					t_ray;

typedef struct t_player
{
	int			x_map;
	int			y_map;
	double		x_pos;
	double		y_pos;
	int			orientation;
	double		direction;
	double		dx;
	double		dy;
	int			scale;
}				t_player;

typedef struct t_map
{
	char		*norh_texture;
	char		*south_texture;
	char		*west_texture;
	char		*est_texture;
	t_mlx_image	*north_tex;
	t_mlx_image	*south_tex;
	t_mlx_image	*west_tex;
	t_mlx_image	*est_tex;
	int			*floor_color;
	int			*ceiling_color;
	int			*start_position;
	int			width;
	int			height;
	int			start;
	int			last;
	int			iterator;
}				t_map;

typedef struct s_image
{
	t_mlx_image	*image;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_image;

typedef struct t_game
{
	t_map		*map_data;
	t_ray		*ray;
	t_mlx		*mlx;
	t_player	*player;
	void		*win;
	char		**map;
	int			map_width;
	int			map_heigth;
	t_image		image;
	char		last_ray;
	char		last_step;
}				t_game;	

//	Rendering functions
void		render_map(t_game *game);
void		render_texture(t_game *game, int i, double hauteur, int x);
void		fix_it_hihi(t_game *game);
void		ft_add_vertical(t_game *game, t_ray *ray, int i);
void		ft_actualise_map(t_game *game, t_ray *ray);
uint32_t	color_to_rgb(uint32_t r, uint32_t g, uint32_t b);
int			square_shape(t_image *image, int x_pos, int y_pos, uint32_t color);
uint32_t	pixel_to_color(t_mlx_image *tex, uint32_t x_pos, uint32_t y_pos);
void		draw_pixel(t_mlx_image *img, uint32_t x,
				uint32_t y, uint32_t color);
t_mlx_image	*textur_to_draw(t_game *game);
void		draw_texture(t_game *game, uint32_t pos_x, uint32_t pos_y);
void		paint_in_black(t_game *game);
void		initialise_map(t_game *game);

//	game mechanics
void		ft_move_w(t_game *game);
void		ft_move_s(t_game *game);
void		ft_move_a(t_game *game);
void		ft_move_d(t_game *game);
void		move(t_game *game, char c);
void		ft_rotate_left(t_game *game);
void		ft_rotate_right(t_game *game);
bool		is_in_wall(t_game *game, int point_x, int point_y);
void		hook_second(void *param);

//	Raycasting and maths
void		ft_init_ray(t_game *game, t_ray *ray, int i);
void		ft_dda(t_game *game, t_ray *ray);
int			raycaster(t_game *game, t_ray *ray, int i);
int			ray_fov(t_game *state);
double		deg_to_rad(double a);
double		ft_fabs(double x);
double		ft_wrap_angle(double angle);
void		ft_fishey(t_game *game, t_ray *ray);
void		ft_step_y(t_ray *ray);
void		ft_step_x(t_ray *ray);
void		ft_small_step(t_ray *ray, char c);
void		ft_nb_step_dx(t_game *game, t_ray *ray);
void		ft_nb_step_dy(t_game *game, t_ray *ray);
void		ft_nb_step(t_game *game, t_ray *ray);
void		ft_fixhit2(t_game *game, t_ray *ray);
int			validate_file(t_game *game);
//	Parsing functions
int			last_seen_at(char *str, char elem);
int			any_before_after(char **map, int current_line);
int			look_in_space(int current_line, t_game *game, int pos);
int			parser_helper(t_game *game, int temp, int inc);
int			ft_ftoi(double x);
void		map_size_init(t_game *game);
void		load_image(t_game *state);
int			verify_extention(char *str, const char *extention);
int			validate_file(t_game *game);
void		player_direction(t_game *game);
void		ft_lst_add_frontd(t_dlist **currlist, t_dlist *newnode);
void		ft_lstiterd(t_dlist *currlist, void (*f) (void *));
void		ft_lst_add_backd(t_dlist **currlist, t_dlist *node);
int			ft_all(char *string, char comp);
int			ft_between(char *string, char comp);
int			verif_len(t_dlist stuff);
int			verif_wall(t_dlist stuff);
int			ft_char_count(char *str, int cmp);
int			verif_param(t_dlist map, char param);
int			verif_map_content(t_dlist map);
void		ft_cleart_dlist(t_dlist **currlist, void (*del)(void *));
void		ft_clearnode(t_dlist *currlist, void (*del)(void *));
t_dlist		*tile_row(t_dlist *map, int y);
t_dlist		*tile_all(t_dlist *map);
int			get_next_line(int fd, char **str);
t_dlist		*mapcreator(char *str);
int			ft_lst_lenght(t_dlist *currlist);
char		**map_init(t_dlist *map);
void		ft_cleart_dlist(t_dlist **currlist, void (*del)(void *));
t_dlist		*verif(t_dlist *map);
t_dlist		*player_node(t_dlist *map);
int			assert(int value, char *str);
int			ft_count_all(char **str, char cmp);
t_dlist		*ft_lstnewl(void *content);
char		freelist(char **list);
int			loop_directions(t_game *state);
void		free_list(t_dlist *head);
t_map		*init_map(void);
char		*skip_empty_line(char *str);
int			parsing(t_game *game, int temp);
int			was_in_set(char *str, char *set);
int			parse_location(t_game *game, int found, int inc);
int			delete_texture(t_map *map);
int			only_space(char *str);
void		resize_map(t_game *game, int len, int width, int iter);
int			verif_number(char **strs);
int			any_one_above(t_game *map, int current_line, int pos);
int			verif_no_space(t_game *game, int pos);
int			any_one_above_line(t_game *map, int current_line);
int			any_one_bellow(char **map, int current_line, int pos);
int			any_one_bellow_line(char **map, int current_line);
int			look_in_space(int current_line, t_game *game, int pos);
void		*ft_free(void *content);
int			*get_color(char *str);
void		ft_poll_color(char *str, t_map *map, int inc);
void		ft_poll_texture(char *str, t_map *map, int inc);
int			valid_range(int *numbers);
void		hook(void *param);
t_dlist		*ft_lst_lastnode(t_dlist *currlist);
t_dlist		*ft_lst_firstnode(t_dlist *currlist);
t_dlist		*ft_lst_prevnode(t_dlist *currlist);
t_dlist		*ft_lst_nextnode(t_dlist *currlist);
t_dlist		*node_init(void *content);
void		init_this(t_game *state);
void		init_map_size(t_game *game);
#endif 
