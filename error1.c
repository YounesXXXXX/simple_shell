#include "shell.h"

/**
 * _xerratoi - converts a string to an integer
 * @s: string to be converted
 * Return: 0 if no numbers in string, Else converted number
 *       -1 on error
 */
int _xerratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * xprint_error - prints an error message
 * @info: parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, Else converted number
 *        -1 on error
 */
void xprint_error(xinfo_t *info, char *estr)
{
	_xeputs(info->fname);
	_xeputs(": ");
	xprint_d(info->line_count, STDERR_FILENO);
	_xeputs(": ");
	_xeputs(info->argv[0]);
	_xeputs(": ");
	_xeputs(estr);
}

/**
 * xprint_d - function prints a decimal (integer) number (base 10)
 * @input: input
 * @fd: filedescriptor to write to
 *
 * Return: number of characters printed
 */
int xprint_d(int input, int fd)
{
	int (*__xputchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__xputchar = _xeputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__xputchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__xputchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__xputchar('0' + current);
	count++;

	return (count);
}

/**
 * xconvert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *xconvert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * xremove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void xremove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
