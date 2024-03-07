/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoraich <akoraich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:26:52 by sgouzi            #+#    #+#             */
/*   Updated: 2024/03/07 00:56:27 by akoraich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	get_rest(char **static_var, int len)
{
	char	*rest;
	int		i;

	i = 0;
	while ((*static_var)[len + i])
		i++;
	rest = malloc((i + 1) * sizeof(char));
	i = 0;
	while ((*static_var)[len])
	{
		rest[i] = (*static_var)[len];
		i++;
		len++;
	}
	rest[i] = '\0';
	ft_free((*static_var));
	(*static_var) = rest;
}

char	*make_line(char **static_var)
{
	char	*full_line;
	int		len;

	len = 0;
	if ((*static_var)[len] == '\0')
		return (NULL);
	while ((*static_var)[len] && (*static_var)[len] != '\n')
		len++;
	if ((*static_var)[len] && (*static_var)[len] == '\n')
		len++;
	full_line = malloc((len + 1) * sizeof(char));
	if (full_line == NULL)
		return (NULL);
	len = 0;
	while ((*static_var)[len] && (*static_var)[len] != '\n')
	{
		full_line[len] = (*static_var)[len];
		len++;
	}
	if ((*static_var)[len] == '\n')
	{
		full_line[len] = (*static_var)[len];
		len++;
	}
	full_line[len] = '\0';
	get_rest(static_var, len);
	return (full_line);
}

char	*get_next_line(int fd)
{
	static char	*static_var;
	char		*buff;
	ssize_t		bytes_read;
	char		*full_line;

	bytes_read = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
	{
		if (static_var)
			return (free(static_var), NULL);
		return (NULL);
	}
	while (is_line(static_var) == 0 && bytes_read > 0)
	{
		buff = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
		if (buff == NULL)
			return (NULL);
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			ft_free(buff);
			return (NULL);
		}
		buff[bytes_read] = '\0';
		static_var = ft_strjoin(static_var, buff);
		if (static_var == NULL)
			return (ft_free(static_var), ft_free(buff), NULL);
		ft_free(buff);
	}
	full_line = make_line(&static_var);
	return (full_line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	fd = open("text.txt", O_RDONLY);
// 	i = 0;
// 	while (i < 100)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		free(line);
// 		i++;
// 	}
// 	return (0);
// }
