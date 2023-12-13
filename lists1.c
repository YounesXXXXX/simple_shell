#include "shell.h"

/**
 * xlist_len - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t xlist_len(const xlist_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * xlist_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **xlist_to_strings(xlist_t *head)
{
	xlist_t *node = head;
	size_t i = xlist_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_xstrlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _xstrcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * xprint_list - prints all elements of a xlist_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t xprint_list(const xlist_t *h)
{
	size_t i = 0;

	while (h)
	{
		_xputs(xconvert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_xputs(h->str ? h->str : "(nil)");
		_xputs("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * xnode_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: next character after prefix to match
 *
 * Return: match node or null
 */
xlist_t *xnode_starts_with(xlist_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = xstarts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * xget_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t xget_node_index(xlist_t *head, xlist_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
