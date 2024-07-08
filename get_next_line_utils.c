/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilastra- <ilastra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:22:48 by ilastra-          #+#    #+#             */
/*   Updated: 2024/06/11 11:03:34 by ilastra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Funciones auxiliares utilizadas por get_next_line.c. 
   Funciones básicas de manipulación de cadenas:
*/

/* ft_strlen: Calcula la longitud de una cadena.
*/

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/* ft_strdup: Duplica una cadena.
*/

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	i;

	i = 0;
	dup = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

/* ft_strchr: Encuentra la primera aparición de un carácter en una cadena.
*/

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

/* ft_strjoin: Une dos cadenas.
*/

char	*ft_strjoin(char *s1, const char *s2)
{
	char	*result;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1)
		s1 = ft_strdup("");
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (ft_free(&s1));
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j])
		result[i++] = s2[j++];
	result[i] = '\0';
	free(s1);
	return (result);
}

/* ft_substr: Extrae una subcadena de una cadena.
*/

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	sub = malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
