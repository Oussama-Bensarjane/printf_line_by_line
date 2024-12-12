#include "get_next_line.h"

char    *new_line(int fd, char *static_buf)
{
    int     _read_byt;
    char    *buffer;
    buffer = malloc((BUFFER_SIZE + 1));
    if(!buffer)
        return (NULL);
    _read_byt = 1;
    while(!ft_strchr(static_buf, '\n') && _read_byt != 0)
    {
        _read_byt = read(fd, buffer, BUFFER_SIZE);
        if(_read_byt == -1)
        {
            free(static_buf);
            free(buffer);
            return (NULL);
        }
        else if(_read_byt == 0)
        {
            free(buffer);
            return (static_buf);
        }
        buffer[_read_byt] = '\0';
        static_buf = ft_strjoin(static_buf, buffer);
    }
    free(buffer);
    return (static_buf);
}

char    *grep_line(char *s)
{
    int i;
	char *dst;

    i = 0;
    if (!s[i])
        return (NULL);
    while (s[i] && s[i] != '\n')
        i++;
    if (s[i] == '\n')
        i++;
    dst = malloc (i + 1);
	if (!dst)
		return (NULL);
    i = 0;
	while (s[i] && s[i] != '\n')
	{
        dst[i] = s[i];
        i++;
	}
    if (s[i] == '\n')
    {
        dst[i] = s[i];
        i++;
    }
    dst[i] = '\0';
    return (dst);
}

char    *next_line(char *s)
{
    int i;
    int j;
    char *buf;

    i = 0;
    while (s[i] && s[i] != '\n')
        i++;
    if (!s[i])
    {
        free(s);
        return (NULL);
    }
    buf = malloc(ft_strlen(s) - i + 1);
    if (!buf)
    {   
        free(s);
        return (NULL);
    }
    i++;
    j = 0;
    while (s[i])
        buf[j++] = s[i++];
    buf[j] = '\0';
    free(s);
    return (buf);
}

char    *get_next_line(int fd)
{
    static char *static_buf;
    char        *the_line;


    if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
        return (NULL);
    static_buf = new_line(fd, static_buf);
    if(!static_buf)
        return (NULL);
    the_line = grep_line(static_buf);
    static_buf = next_line(static_buf);
    return (the_line);
}