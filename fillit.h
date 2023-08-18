/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjamsa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:17:28 by jjamsa            #+#    #+#             */
/*   Updated: 2022/01/21 15:22:30 by jjamsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_tet
{
	char	alphabet;
	int		x[4];
	int		y[4];
}					t_tet;

typedef struct s_map
{
	int		size;
	char	**array;
}					t_map;

int		fillit(const int fd);
int		validate_file(const int fd);
char	***create_grid(int char_count, char *buff);
void	print_solution(char **solution);
char	**solver(t_tet *tet_array, int nb);
void	free_array(char **arr, int until);
void	free_grid(char ***grid, int until);
t_tet	*create_tet_array(int char_count, char ***grid);
t_map	*make_map(int size);

#endif
