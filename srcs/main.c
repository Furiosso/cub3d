/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:20:32 by pavicent          #+#    #+#             */
/*   Updated: 2025/06/24 19:20:34 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	fill_values(int row, int column)
{
	static const double	values[][4] = {
	{-1.00, +1.00, +0.00, +0.00},
	{+0.00, +0.00, +1.00, -1.00},
	{+0.00, +0.00, +0.66, -0.66},
	{+0.66, -0.66, +0.00, +0.00}
	};

	return (values[row][column]);
}

void	get_player_values(t_cub3D *data, int x, int y)
{
	int	i;
	int	player_dir;

	data->vectors = ft_alloc(sizeof(t_vectors), 1);
	data->vectors->pos_y = x + 0.5;
	data->vectors->pos_x = y + 0.5;
	if (data->map_arr[y][x] == 'N')
		player_dir = 0;
	if (data->map_arr[y][x] == 'S')
		player_dir = 1;
	if (data->map_arr[y][x] == 'E')
		player_dir = 2;
	if (data->map_arr[y][x] == 'W')
		player_dir = 3;
	i = 0;
	data->vectors->dir_x = fill_values(i++, player_dir);
	data->vectors->dir_y = fill_values(i++, player_dir);
	data->vectors->plane_x = fill_values(i++, player_dir);
	data->vectors->plane_y = fill_values(i++, player_dir);
}

void	set_player_pos(char **map, t_cub3D *data)
{
	int		x;
	int		y;
	char	*str;

	y = 0;
	str = "NSWE";
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_strchr(str, map[y][x]))
			{
				get_player_values(data, x, y);
				return ;
			}
			x++;
		}
		y++;
	}
}

int	main(int ac, char **av)
{
	t_cub3D	*data;

	if (ac != 2)
		ft_print_message_and_exit("Incorrect number of arguments", 1);
	if (!ft_check_extention(av[1], ".cub"))
		ft_print_message_and_exit("Not valid .cub extention", 1);
	data = ft_alloc(sizeof(t_cub3D), 1);
	parsing(av[1], data);
	set_player_pos(data->map_arr, data);
	execute_game(data);
	ft_alloc(0, 0);
}
