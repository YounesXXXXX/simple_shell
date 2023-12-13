#include "shell.h"

/**
 * _xmyhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _xmyhistory(xinfo_t *info)
{
	xprint_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, Else 1 on error
 */
int unset_alias(xinfo_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _xstrchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = xdelete_node_at_index(&(info->alias),
		xget_node_index(info->alias, xnode_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, Else 1 on error
 */
int set_alias(xinfo_t *info, char *str)
{
	char *p;

	p = _xstrchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (xadd_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, Else 1 on error
 */
int print_alias(xlist_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _xstrchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_xputs(p + 1);
		_xputs("'\n");
		return (0);
	}
	return (1);
}

/**
 * _xmyalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _xmyalias(xinfo_t *info)
{
	int i = 0;
	char *p = NULL;
	xlist_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _xstrchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(xnode_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
