#include "shell.h"

/**
 * xadd_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
xlist_t *xadd_node(xlist_t **head, const char *str, int num)
{
	xlist_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(xlist_t));
	if (!new_head)
		return (NULL);
	_xmemset((void *)new_head, 0, sizeof(xlist_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _xstrdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * xadd_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
xlist_t *xadd_node_end(xlist_t **head, const char *str, int num)
{
	xlist_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(xlist_t));
	if (!new_node)
		return (NULL);
	_xmemset((void *)new_node, 0, sizeof(xlist_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _xstrdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * xprint_list_str - prints only the str element of a xlist_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t xprint_list_str(const xlist_t *h)
{
	size_t i = 0;

	while (h)
	{
		_xputs(h->str ? h->str : "(nil)");
		_xputs("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * xdelete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int xdelete_node_at_index(xlist_t **head, unsigned int index)
{
	xlist_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * xfree_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void xfree_list(xlist_t **head_ptr)
{
	xlist_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
