#include "shell.h"

/**
 * xinteractive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, Else 0
 */
int xinteractive(xinfo_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * xis_delim - checks if char is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, Else 0
 */
int xis_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_xisalpha - checks for alphabetic char
 *@c: char to input
 *Return: 1 if c is alphabetic, Else 0
 */

int _xisalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_xatoi - converts a string to an int
 *@s: the string to be converted
 *Return: 0 if no numbers in string, Else converted number
 */

int _xatoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
