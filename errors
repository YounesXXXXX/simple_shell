#include "shell.h"

/**
 *_xeputs - prints an input string
 * @str: string to be printed
 *
 * Return: Nothing
 */
void _xeputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_xeputchar(str[i]);
		i++;
	}
}

/**
 * _xeputchar - writes the char c to stderr
 * @c: char to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _xeputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _xputfd - writes the char c to given fd
 * @c: The char to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _xputfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_xputsfd - prints an input string
 * @str: string to be printed
 * @fd: filedescriptor to write to
 *
 * Return: number of chars put
 */
int _xputsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _xputfd(*str++, fd);
	}
	return (i);
}
