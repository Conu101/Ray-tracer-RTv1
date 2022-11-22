/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouve <ctrouve@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:40:03 by ctrouve           #+#    #+#             */
/*   Updated: 2022/10/13 13:46:43 by ctrouve          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Function name: new_line

Parameters: 
	int fd: file descriptor
	char **line: line read last
	char **stat: static accremented during previous readings
Variables:
	size_t len: index within stat where the next newline char is found.
	char *temp: temporary value storage variable
Return values:
	if there is a new line at index len>0
		malloc the string *line with the value of the substring in
		*stat between index 0 and len
	or if the null-terminating byte is found in stat[fd]
		malloc the string *line with the value of stat[fd]
		strdel(&stat[fd])
	return 1 
*/
static int	new_line(int fd, char **stat, char **line)
{
	size_t	len;
	char	*temp;

	len = 0;
	while (stat[fd][len] != '\n' && stat[fd][len] != '\0')
		len++;
	if (stat[fd][len] == '\n')
	{
		*line = ft_strsub(stat[fd], 0, len);
		temp = ft_strdup(stat[fd] + len + 1);
		ft_strdel(&stat[fd]);
		stat[fd] = temp;
	}
	else
	{
		*line = ft_strdup(stat[fd]);
		ft_strdel(&stat[fd]);
	}
	return (1);
}

/*
Function name: return_value

Parameters: 
	same as get_next_line and
	ssize_t n_bytes read after last while loop of n_bytes > 0
	char **stat: static accremented during previous readings

Return values:
	if error: 
	-> return -1
	if last reading read 0 bytes and the static is empty:(empty file)
		sets the line to empty line
	if the 1st byte is a null-terminating byte
		malloc the string *line with the value of entire *stat = NULL
		free(*stat), set it to NULL
	-> return 0 (end of reading)
	else the return value depends on the presence of a new line or not
	check with auxillary function	int	new_line(char **stat, char **line)
*/
static int	return_value(int fd, ssize_t n_bytes, char **stat, char **line)
{
	if (n_bytes < 0)
		return (-1);
	else if (n_bytes == 0 && stat[fd] == NULL)
		return (0);
	else if (stat[fd][0] == '\0')
	{
		*line = ft_strdup(stat[fd]);
		ft_strdel(&stat[fd]);
		return (0);
	}
	return (new_line(fd, stat, line));
}

/*
Function name: get_next_line

Prototype: int get_next_line(int fd, char **line)

Parameters: fd = file descriptor for reading 
			**line = The value of what has been read

Return value: 1 : A line has been read | 0 : EOF has been reached |
			 -1 : An error happened

External Functions : read, malloc, free

Variables:
static char *stat[FD_SIZE] 
	Remains in the memory space during the execution of the 
	entire program. The default initialization value of a 
	static variable is zero (default with word "static").
	(see https://www.upgrad.com/blog/static-variable-in-c/)
char buff[BUFF_SIZE + 1]
	Buffer where the reading of the file/input is sent by blocks of 
	BUFF_SIZE
int n_bytes
	number of bytes read by the read function from the file/input
	ssize_t Used for a count of bytes or an error indication
char *temp
	temporary storage pointer, stores a value temporarily for using 
	it in another place without changing the origin variable value.
*/
int	get_next_line(int fd, char **line)
{
	char		buff[BUFF_SIZE + 1];
	ssize_t		n_bytes;
	static char	*stat[FD_SIZE];
	char		*temp;

	if (fd < 0 || fd >= FD_SIZE || !line || BUFF_SIZE < 1)
		return (-1);
	n_bytes = read(fd, buff, BUFF_SIZE);
	while (n_bytes > 0)
	{
		buff[n_bytes] = '\0';
		if (stat[fd] == NULL)
			stat[fd] = ft_strdup(buff);
		else
		{
			temp = ft_strjoin(stat[fd], buff);
			free(stat[fd]);
			stat[fd] = temp;
		}
		if (ft_strchr(buff, '\n'))
			break ;
		n_bytes = read(fd, buff, BUFF_SIZE);
	}
	return (return_value(fd, n_bytes, stat, line));
}
