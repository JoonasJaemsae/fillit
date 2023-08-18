/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjamsa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:14:00 by jjamsa            #+#    #+#             */
/*   Updated: 2022/01/21 15:19:30 by jjamsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	print_solution(char **solution)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (solution[i] != 0)
	{
		j = 0;
		while (solution[i][j] != '\0')
		{
			write(1, &(solution[i][j]), 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
	free_array(solution, i + 1);
	free(solution);
}

int	output(const int fd)
{
	int	result;

	result = fillit(fd);
	if (result < 0)
	{
		write(1, "error\n", 6);
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
	{
		write(2, "usage: Insert one argument after ./fillit\n", 42);
		return (-1);
	}
	else
	{
		fd = (const int) open(argv[1], O_RDWR);
		if (fd == -1)
		{
			write(2, "open() error\n", 13);
			return (-1);
		}
		if (output(fd) == -1)
			return (-1);
	}
	if (close(fd) == -1)
	{
		write(2, "close() error\n", 14);
		return (-1);
	}
	return (0);
}
