#include "shell.h"

/**
 * xis_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int xis_chain(xinfo_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * xcheck_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void xcheck_chain(xinfo_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * xreplace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int xreplace_alias(xinfo_t *info)
{
	int i;
	xlist_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = xnode_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _xstrchr(node->str, '=');
		if (!p)
			return (0);
		p = _xstrdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * xreplace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int xreplace_vars(xinfo_t *info)
{
	int i = 0;
	xlist_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_xstrcmp(info->argv[i], "$?"))
		{
			xreplace_string(&(info->argv[i]),
				_xstrdup(xconvert_number(info->status, 10, 0)));
			continue;
		}
		if (!_xstrcmp(info->argv[i], "$$"))
		{
			xreplace_string(&(info->argv[i]),
				_xstrdup(xconvert_number(getpid(), 10, 0)));
			continue;
		}
		node = xnode_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			xreplace_string(&(info->argv[i]),
				_xstrdup(_xstrchr(node->str, '=') + 1));
			continue;
		}
		xreplace_string(&info->argv[i], _xstrdup(""));

	}
	return (0);
}

/**
 * xreplace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int xreplace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
