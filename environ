#include "shell.h"

/**
 * _xmyenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _xmyenv(xinfo_t *info)
{
	xprint_list_str(info->env);
	return (0);
}

/**
 * _xgetenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_xgetenv(xinfo_t *info, const char *name)
{
	xlist_t *node = info->env;
	char *p;

	while (node)
	{
		p = xstarts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _xmysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _xmysetenv(xinfo_t *info)
{
	if (info->argc != 3)
	{
		_xeputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_xsetenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _xmyunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _xmyunsetenv(xinfo_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_xeputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_xunsetenv(info, info->argv[i]);

	return (0);
}

/**
 * xpopulate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int xpopulate_env_list(xinfo_t *info)
{
	xlist_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		xadd_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
