/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   making_grid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalmi <lsalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:07:37 by lsalmi            #+#    #+#             */
/*   Updated: 2022/01/21 14:55:38 by jjamsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_map	*make_map(int size)
{
	t_map	*map;
	int		i;
	int		j;

	i = 0;
	map = (t_map *) malloc(sizeof(t_map));
	if (map == NULL)
		exit(-1);
	map->array = (char **) malloc(sizeof(char *) * (size + 1));
	if (map->array == NULL)
		exit(-1);
	map->size = size;
	while (i < size)
	{
		j = 0;
		map->array[i] = (char *) malloc(sizeof(char) * (size + 1));
		if (map->array[i] == NULL)
			exit(-1);
		while (j < size)
			map->array[i][j++] = '.';
		map->array[i++][j] = '\0';
	}
	map->array[i] = (char *) '\0';
	return (map);
}

void	free_grid(char ***grid, int until)
{
	int	i;
	int	j;

	i = 0;
	while (i < until)
	{
		j = 0;
		while (j < 5)
		{
			free(grid[i][j]);
			j++;
		}
		free(grid[i]);
		i++;
	}
}

void	free_array(char **arr, int until)
{
	int	i;

	i = 0;
	while (i < until)
	{
		free(arr[i]);
		i++;
	}
}

int	fill_grid(char ***grid, char *buff, int *chr)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	*grid = (char **) malloc(sizeof(char *) * 5);
	if (*grid == NULL)
		return (-1);
	while (*chr % 21 != 0 && row < 4)
	{
		col = 0;
		(*grid)[row] = (char *) malloc(sizeof(char) * 5);
		if ((*grid)[row] == NULL)
		{
			free_array(*grid, row);
			free(*grid);
			return (-1);
		}
		while (col < 4)
			(*grid)[row][col++] = buff[(*chr)++ - 1];
		(*grid)[row++][col] = '\0';
		(*chr)++;
	}
	return (0);
}

char	***create_grid(int char_count, char *buff)
{
	char	***grid;
	int		p;
	int		chr;

	p = 0;
	chr = 1;
	grid = (char ***) malloc(sizeof(char **) * ((char_count / 21) + 1));
	if (grid == NULL)
		return (NULL);
	while (p < (char_count / 21))
	{
		if (fill_grid(&(grid[p]), buff, &chr) == -1)
		{
			free_grid(grid, p);
			free(grid);
			return (NULL);
		}
		grid[p++][4] = 0;
		chr++;
	}
	grid[p] = 0;
	return (grid);
}
