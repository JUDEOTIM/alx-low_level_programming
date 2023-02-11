#include "lists.h"

/**
 * insert_dnodeint_at_index - inserts a new node at a given position.
 * @h: Head to a dlistint_int list.
 * @idx: Index to fix node at.
 * @n: Value to store in the new node.
 *
 * Return: NULL - If not successful.
 *	   O/w - Address of the new node.
 */
dlistint_t *insert_dnodeint_at_index(dlistint_t **h, unsigned int idx, int n)
{
	dlistint_t *curr = *h, *new, *prev;
	unsigned int i = 0;

	if (idx == 0)
		return (add_dnodeint(h, n));

	while (curr)
	{
		if (i == idx)
			break;
		i++;
		curr = curr->next;
	}
	if (!curr && i == idx)
		return (add_dnodeint_end(h, n));

	if (i == idx && curr)
	{
		new = malloc(sizeof(dlistint_t));
		if (new == NULL)
			return (NULL);
		new->n = n;
		prev = curr->prev;
		new->next = curr;
		new->prev = prev;
		curr->prev = new;
		prev->next = new;
		return (new);
	}

	return (NULL);
}
