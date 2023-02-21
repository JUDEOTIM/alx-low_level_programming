#include "hash_tables.h"

/**
 * shash_table_create - Creates a sorted hash table.
 * @size: Size of the array/hash table.
 *
 * Return: A pointer to the newNodely created hash table.
 *	   O/w - NULL.
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *ht;
	unsigned long int i;

	ht = malloc(sizeof(shash_table_t));
	if (ht == NULL)
		return (NULL);

	ht->size = size;
	ht->array = malloc(sizeof(shash_node_t *) * size);
	if (ht->array == NULL)
		return (NULL);

	/* let all shash nodes be initialized to NULL. */
	for (i = 0; i < size; i++)
		ht->array[i] = NULL;

	ht->shead = NULL;
	ht->stail = NULL;
	return (ht);
}

/**
 * shash_table_set - Add or update an element in a sorted
 *		    hash table.
 * @ht: A pointer to the hash table.
 * @key: The key to add - cannot be an empty string.
 * @value: The value associated with key.
 *
 * Return: If it succeeds - 1.
 *         Otherwise - 0.
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	unsigned long int key_idx;
	char *value_cpy;
	shash_node_t *newNode, *exist_node;

	if (!ht || !key || !value || *key == '\0')
		return (0);
	value_cpy = strdup(value);
	if (!value_cpy)
		return (0);

	key_idx = key_index((const unsigned char *)key, ht->size);
	exist_node = ht->shead;
	for (; exist_node; exist_node = exist_node->snext)
	{
		if (strcmp(exist_node->key, key) == 0)
		{
			free(exist_node->value);
			exist_node->value = value_cpy;
			return (1);
		}
	}
	newNode = malloc(sizeof(shash_node_t));
	if (newNode == NULL)
	{
		free(value_cpy);
		return (0);
	}
	newNode->value = value_cpy;
	newNode->key = strdup(key);
	if (newNode->key == NULL)
	{
		free(value_cpy);
		free(newNode);
		return (0);
	}
	newNode->next = ht->array[key_idx];
	ht->array[key_idx] = newNode;
	if (!sort_list(ht, newNode, key))
		return (0);
	return (1);
}

/**
 * sort_list - Sorts a doubly linked list in ascending order.
 * @ht: ...
 * @newNode: ...
 * @key: ...
 * Return: 0 - If it fails.
 *	   Otherwise - 1.
 */
int sort_list(shash_table_t *ht, shash_node_t *newNode, const char *key)
{
	shash_node_t *tmp;

	if (!ht || !newNode || !key || *key == '\0')
		return (0);

	if (ht->shead == NULL)
	{
		newNode->snext = NULL;
		newNode->sprev = NULL;
		ht->shead = newNode;
		ht->stail = newNode;
	}
	else if (strcmp(ht->shead->key, key) > 0)
	{
		newNode->sprev = NULL;
		newNode->snext = ht->shead;
		ht->shead->sprev = newNode;
		ht->shead = newNode;
	}
	else
	{
		tmp = ht->shead;
		while (tmp->snext && strcmp(tmp->snext->key, key) < 0)
			tmp = tmp->snext;
		newNode->snext = tmp->snext;
		newNode->sprev = tmp;
		if (tmp->snext == NULL)
			ht->stail = newNode;
		else
			tmp->snext->sprev = newNode;
		tmp->snext = newNode;
	}
	return (1);
}

/**
 * shash_table_get - Retrieve the value associated with
 *                  a key in a sorted hash table.
 * @ht: A pointer to the hash table.
 * @key: The key.
 *
 * Return: The value associated with key in ht.
 *         Otherwise, if the key is not found - NULL.
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	unsigned long int key_idx;
	shash_node_t *node;

	if (!ht || !key || *key == '\0')
		return (NULL);

	key_idx = key_index((const unsigned char *)key, ht->size);
	if (key_idx >= ht->size)
		return (NULL);

	node = ht->array[key_idx];
	for (; node; node = node->snext)
	{
		if (strcmp(node->key, key) == 0)
			return (node->value);
	}

	return (NULL);
}

/**
 * shash_table_print - Prints a sorted hash table in order.
 * @ht: A pointer to the sorted hash table.
 */
void shash_table_print(const shash_table_t *ht)
{
	shash_node_t *node;

	if (ht == NULL)
		return;

	node = ht->shead;
	printf("{");
	while (node)
	{
		printf("'%s': '%s'", node->key, node->value);
		if (node->snext)
			printf(", ");
		node = node->snext;
	}
	printf("}\n");
}


/**
 * shash_table_print_rev - Prints a sorted hash table in
 *			   reverse order.
 * @ht: A pointer to the sorted hash table.
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	shash_node_t *node;

	if (ht == NULL)
		return;

	node = ht->stail;
	printf("{");
	while (node)
	{
		printf("'%s': '%s'", node->key, node->value);
		if (node->sprev)
			printf(", ");
		node = node->sprev;
	}
	printf("}\n");
}

/**
 * shash_table_delete - Deletes a sorted hash table.
 * @ht: A pointer to the sorted hash table.
 */
void shash_table_delete(shash_table_t *ht)
{
	shash_node_t *tmp;

	if (ht == NULL)
		return;

	while (ht->shead)
	{
		tmp = ht->shead->snext;
		free(ht->shead->key);
		free(ht->shead->value);
		free(ht->shead);
		ht->shead = tmp;
	}

	free(ht->array);
	free(ht);
}
