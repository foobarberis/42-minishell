/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_file_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:32:22 by mbarberi          #+#    #+#             */
/*   Updated: 2023/05/01 10:26:06 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlc.h"
#include <fcntl.h> /* for open(2) */

#define READALL_CHUNK 262144

/**
 * @brief Helper function to compute the size of the file by repeatedly adding
 * the return values of read(2).
 * @param file A string containing the name of the file to process.
 * @return The size of the file or -1 if an error occured.
 */
static ssize_t	f_get_file_size(char *file)
{
	int		fd;
	ssize_t	r;
	ssize_t	size;
	char	buf[READALL_CHUNK];

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	size = 0;
	while (1)
	{
		r = read(fd, buf, READALL_CHUNK);
		if (r < 0)
			return (-1);
		if (!r)
			break ;
		size += r;
	}
	close(fd);
	return (size);
}

/**
 * @brief Store a file in an array.
 * @param file A string containing the name of the file to process.
 * @return An array containing the file or NULL if an error occured.
 */
char	*f_file_to_array(char *file)
{
	int		fd;
	ssize_t	size;
	char	*buf;

	size = f_get_file_size(file);
	if (size < 0)
		return (NULL);
	buf = malloc(size + 1);
	if (!buf)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (read(fd, buf, size) < 0)
		return (close(fd), free(buf), NULL);
	buf[size] = '\0';
	close(fd);
	return (buf);
}
