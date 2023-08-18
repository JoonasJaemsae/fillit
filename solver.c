/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalmi <lsalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:29:57 by lsalmi            #+#    #+#             */
/*   Updated: 2022/01/21 15:14:48 by jjamsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	rounded_sqrt(int nb)
{
	int	size;

	size = 2;
	while ((size * size) < (nb * 4))
		size++;
	return (size);
}

int	place_tet(t_map *map, t_tet piece, int row, int col)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if ((row + piece.y[i] < map->size)
			&& (col + piece.x[i] < map->size)
			&& (col + piece.x[i] >= 0)
			&& (map->array[row + piece.y[i]][col + piece.x[i]] == '.'))
		{
			map->array[row + piece.y[i]][col + piece.x[i]] = piece.alphabet;
		}
		else
		{
			return (-1);
		}
		i++;
	}
	return (0);
}

int	alphabet_to_dot(t_map *map, t_tet piece, int row, int col)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if ((row + piece.y[i] < map->size)
			&& (col + piece.x[i] < map->size)
			&& (col + piece.x[i] >= 0)
			&& (map->array[row + piece.y[i]][col + piece.x[i]]
			== piece.alphabet))
		{
			map->array[row + piece.y[i]][col + piece.x[i]] = '.';
		}
		i++;
	}
	return (0);
}

int	solve_map(t_map *map, t_tet *tet_array, int nb, int i)
{
	int	col;
	int	row;

	row = 0;
	if (i == nb)
		return (0);
	while (row < map->size)
	{
		col = 0;
		while (col < map->size)
		{
			if (place_tet(map, tet_array[i], row, col) != -1)
			{
				if (solve_map(map, tet_array, nb, i + 1) == 0)
					return (0);
				else
					alphabet_to_dot(map, tet_array[i], row, col);
			}
			else
				alphabet_to_dot(map, tet_array[i], row, col);
			col++;
		}
		row++;
	}
	return (-1);
}

char	**solver(t_tet *tet_array, int nb)
{
	t_map	*map;
	int		size;
	int		i;

	i = 0;
	size = rounded_sqrt(nb);
	map = make_map(size);
	while (solve_map(map, tet_array, nb, i) == -1)
	{
		free_array(map->array, size + 1);
		free(map->array);
		size++;
		map = make_map(size);
	}
	return (map->array);
}
