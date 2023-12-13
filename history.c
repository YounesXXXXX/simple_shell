#include "shell.h"

/**
 * xget_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *xget_history_file(xinfo_t *info)
{
	char *buf, *dir;

	dir = _xgetenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_xstrlen(dir) + _xstrlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_xstrcpy(buf, dir);
	_xstrcat(buf, "/");
	_xstrcat(buf, HIST_FILE);
	return (buf);
}

/**
 * xwrite_history - creates a file, or appends to an existing file
 * @info: parameter struct
 *
 * Return: 1 on success, else -1
 */
int xwrite_history(xinfo_t *info)
{
	ssize_t fd;
	char *filename = xget_history_file(info);
	xlist_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_xputsfd(node->str, fd);
		_xputfd('\n', fd);
	}
	_xputfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * xread_history - reads history from file
 * @info: parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int xread_history(xinfo_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = xget_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			xbuild_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		xbuild_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		xdelete_node_at_index(&(info->history), 0);
	xrenumber_history(info);
	return (info->histcount);
}

/**
 * xbuild_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: history linecount, histcount
 *
 * Return: Always 0
 */
int xbuild_history_list(xinfo_t *info, char *buf, int linecount)
{
	xlist_t *node = NULL;

	if (info->history)
		node = info->history;
	xadd_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * xrenumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: new histcount
 */
int xrenumber_history(xinfo_t *info)
{
	xlist_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
