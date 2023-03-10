/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:35:51 by aguay             #+#    #+#             */
/*   Updated: 2022/03/30 09:56:02 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

bool	g_on;

int	ft_keypress(int keycode, t_vars *vars)
{
	t_map	*map;
	int		*char_x;
	int		*char_y;

	map = vars->map;
	char_x = &vars->map->char_x;
	char_y = &vars->map->char_y;
	if (g_on == false)
	{
		g_on = true;
		if (keycode == vars->escape)
			exit(0);
		else if (keycode == vars->a)
			move_a(vars, char_x, char_y, map);
		else if (keycode == vars->s)
			move_s(vars, char_x, char_y, map);
		else if (keycode == vars->d)
			move_d(vars, char_x, char_y, map);
		else if (keycode == vars->w)
			move_w(vars, char_x, char_y, map);
		g_on = false;
	}
	return (0);
}

int	ft_exit(void)
{
	exit(0);
	return (0);
}

static void	main2xd(t_vars vars, t_data background, t_map map)
{
	mlx_put_image_to_window(vars.mlx, vars.win, background.img, 0, 0);
	render_map(vars, &map);
	vars.map->pos[map.char_y][map.char_x] = '0';
	mlx_hook(vars.win, ON_KEYDOWN, 1L << 0, ft_keypress, &vars);
	mlx_hook(vars.win, ON_DESTROY, 1L << 0, ft_exit, &vars);
	mlx_loop(vars.mlx);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_data	background;
	t_map	map;

	if (argc != 2)
		return (0);
	if (validate_map(argv[1]) == false)
	{
		ft_putstr_fd("Error : map invalid\n", 2);
		return (1);
	}
	g_on = false;
	initialise_map(argv[1], &map);
	vars.map = &map;
	vars.mlx = mlx_init();
	initialise_keysum(&vars);
	vars.win = mlx_new_window(vars.mlx, map.width * 24,
			map.height * 24, "So long");
	background.img = mlx_new_image(vars.mlx, 600, 600);
	background.addr = mlx_get_data_addr(background.img,
			&background.bits_per_pixel, &background.line_length,
			&background.endian);
	main2xd(vars, background, map);
}
