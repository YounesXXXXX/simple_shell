#include "shell.h"

/**
 * xclear_info - initializes xinfo_t struct
 * @info: struct address
 */
void xclear_info(xinfo_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * xset_info - initializes xinfo_t struct
 * @info: struct address
 * @av: argument vector
 */
void xset_info(xinfo_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = xstrtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _xstrdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		xreplace_alias(info);
		xreplace_vars(info);
	}
}

/**
 * xfree_info - free xinfo_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void xfree_info(xinfo_t *info, int all)
{
	xffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			xfree_list(&(info->env));
		if (info->history)
			xfree_list(&(info->history));
		if (info->alias)
			xfree_list(&(info->alias));
		xffree(info->environ);
			info->environ = NULL;
		xbfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
