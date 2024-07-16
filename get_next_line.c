/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilastra- <ilastra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:22:40 by ilastra-          #+#    #+#             */
/*   Updated: 2024/06/11 12:38:59 by ilastra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* ft_free: Libera una cadena asignada con malloc.
*/

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

/*extract_line: Esta función toma un puntero a una cadena (storage) y busca 
un carácter de nueva línea ('\n'). Si lo encuentra, extrae la subcadena desde 
el principio de la cadena hasta (pero sin incluir) el carácter de nueva línea, 
y devuelve una copia de esa subcadena.

update_storage: Esta función actualiza la cadena storage. Elimina la línea 
extraída del principio de la cadena, conservando esencialmente el contenido 
restante después del carácter de nueva línea (si está presente). Devuelve una 
nueva cadena que contiene el contenido restante.
*/

static char	*extract_and_update_line(char **storage)
{
	char			*line;
	char			*newline_pos;
	char			*new_storage;
	unsigned int	start;

	if (!*storage)
		return (NULL);
	newline_pos = ft_strchr(*storage, '\n');
	if (newline_pos)
	{
		line = ft_substr(*storage, 0, newline_pos - *storage + 1);
		start = (newline_pos - *storage) + 1;
		new_storage = ft_substr(*storage, start, ft_strlen(newline_pos + 1));
		ft_free(storage);
		*storage = new_storage;
	}
	else
	{
		line = ft_strdup(*storage);
		ft_free(storage);
	}
	return (line);
}

/*read_and_store: Esta función lee datos del descriptor de archivo (fd) en un 
búfer con un tamaño definido por BUFFER_SIZE. Sigue leyendo hasta que se 
encuentra una nueva línea o se produce un error. Anexa los datos leídos a 
la cadena storage utilizando ft_strjoin.
*/

static char	*read_and_store(int fd, char **storage)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (ft_free(storage));
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		*storage = ft_strjoin(*storage, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (bytes_read < 0)
		return (ft_free(storage));
	if (*storage && **storage == '\0')
		return (ft_free(storage));
	return (*storage);
}

/*La función get_next_line:
Toma un descriptor de archivo (fd) como entrada.
Utiliza una variable estática storage para almacenar los datos leídos del 
archivo hasta ahora.
Comprueba si hay descriptores de archivo no válidos o un tamaño de búfer 
negativo.
Si storage está vacío, le asigna una cadena vacía.
Llama a read_and_store para leer datos del archivo y actualizar el storage.
Si storage se vuelve NULL debido a errores, devuelve NULL.
Llama a extract_line para obtener la siguiente línea del storage.
Llama a update_storage para eliminar la línea extraída del storage.
Devuelve la línea extraída (necesita ser liberada por el llamador).
*/

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!storage)
		storage = ft_strdup("");
	storage = read_and_store(fd, &storage);
	if (!storage)
		return (NULL);
	line = extract_and_update_line(&storage);
	if (!line && storage && storage[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

/* int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc != 2)
	{
		write(1, "Wrong argument count: Must be exactly 2.\n", 41);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		write(1, "Error: Could not open file\n", 27);
		return (1);
	}
	line = NULL;
	while (line = get_next_line(fd) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
} */

/*Compilar
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c 
get_next_line_utils.c -o gnl && ./gnl text.txt
 */
/*
MAIN NORMAL
int	main(int argc, char **argv)
{
	int		fd;
	char	*test_str;

	if (argc != 2)
	{
		write(1, "Wrong argument count: Must be exactly 2.\n", 41);
		return (1);
	}
	test_str = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		write (1, "Error: Could not open file\n", 27);
		return (1);
	}
	while ((test_str = get_next_line(fd)))
	{
		printf("Result: %s", test_str);
		free(test_str);
	}
	close (fd);
	return (0);
}
*/
/* 
MAIN PARA ENTRADA POR TECLADO
int	main(void)
{
	char	*line;

	while ((line = get_next_line(0)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	return (0);
} 
*/