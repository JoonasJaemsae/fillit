/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tet_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjamsa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:45:56 by jjamsa            #+#    #+#             */
/*   Updated: 2022/01/21 15:18:12 by jjamsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	*get_abs_yx(t_tet *data, int row, int col)
{
	int	*abs_yx;

	abs_yx = (int *) malloc(sizeof(int) * 2);
	if (abs_yx == NULL)
	{
		exit(-1);
	}
	data->y[0] = 0;
	data->x[0] = 0;
	abs_yx[0] = row;
	abs_yx[1] = col;
	return (abs_yx);
}

void	assign_relative_coords(char ***grid, t_tet *data, int row, int i)
{
	int	*abs_yx;
	int	col;

	while (row < 4)
	{
		col = 0;
		while (col < 4)
		{
			if ((*grid)[row][col] == '#')
			{
				if (i == 0)
					abs_yx = get_abs_yx(data, row, col);
				else
				{
					data->y[i] = row - abs_yx[0];
					data->x[i] = col - abs_yx[1];
				}
				i++;
			}
			col++;
		}
		row++;
	}
	free(abs_yx);
}

t_tet	get_data(char ***grid, char alphabet)
{
	int		row;
	int		i;
	t_tet	data;

	row = 0;
	i = 0;
	assign_relative_coords(grid, &data, row, i);
	data.alphabet = alphabet;
	return (data);
}

t_tet	*create_tet_array(int char_count, char ***grid)
{
	int		p;
	char	alphabet;
	t_tet	*tet_array;

	p = 0;
	alphabet = 'A';
	tet_array = (t_tet *) malloc(sizeof(t_tet) * (char_count / 21));
	if (tet_array == NULL)
	{
		free_grid(grid, char_count / 21);
		free(grid);
		exit(-1);
	}
	while (p < char_count / 21)
	{
		tet_array[p] = get_data(&(grid[p]), alphabet);
		alphabet++;
		p++;
	}
	return (tet_array);
}
