/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalmi <lsalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:15:06 by lsalmi            #+#    #+#             */
/*   Updated: 2022/01/21 15:06:29 by jjamsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	touching_myself(char **piece, int row, int col)
{
	int	count;

	count = 0;
	while (row < 4)
	{
		col = 0;
		while (col < 4)
		{
			if (piece[row][col] == '#')
			{
				if (col < 3 && piece[row][col + 1] == '#')
					count++;
				if (row < 3 && piece[row + 1][col] == '#')
					count++;
			}
			col++;
		}
		row++;
	}
	if (count < 3 || count > 4)
		return (-1);
	return (0);
}

int	validate_pieces(char ***grid)
{
	int	p;
	int	row;
	int	col;

	p = 0;
	while (grid[p] != NULL)
	{
		row = 0;
		col = 0;
		if (touching_myself(grid[p], row, col) == -1)
			return (-1);
		p++;
	}
	return (0);
}

int	count_hashtags(char ***grid)
{
	int	count;
	int	row;
	int	col;
	int	p;

	p = 0;
	while (grid[p] != NULL)
	{
		count = 0;
		row = 0;
		while (row < 4)
		{
			col = 0;
			while (col < 4)
			{
				if (grid[p][row][col++] == '#')
					count++;
			}
			row++;
		}
		if (count > 4)
			return (-1);
		p++;
	}
	return (0);
}

int	validate_format(const int fd, char *buff)
{
	int	i;
	int	ret;

	i = 1;
	ret = read(fd, buff, 546);
	if (ret > 545 || ret == 0 || ret == -1 || (ret + 1) % 21 != 0)
	{
		return (-1);
	}
	buff[ret] = '\0';
	while (i < 546 && buff[i - 1] != '\0')
	{
		if ((i % 21 == 0) && (buff[i - 1] != '\n'))
			return (-1);
		else if (((i % 21) % 5 == 0) && (buff[i - 1] != '\n'))
			return (-1);
		else if (buff[i - 1] != '.' && buff[i - 1] != '#'
			&& buff[i - 1] != '\n')
			return (-1);
		i++;
	}
	return (i);
}

int	fillit(const int fd)
{
	int		char_count;
	char	buff[546];
	char	***grid;
	char	**solution;
	t_tet	*tet_array;

	char_count = validate_format(fd, buff);
	if (char_count == -1)
		return (-1);
	grid = create_grid(char_count, buff);
	if (grid == NULL)
		return (-1);
	if (count_hashtags(grid) == -1)
		return (-1);
	if (validate_pieces(grid) == -1)
		return (-1);
	tet_array = create_tet_array(char_count, grid);
	solution = solver(tet_array, (char_count / 21));
	print_solution(solution);
	return (0);
}
