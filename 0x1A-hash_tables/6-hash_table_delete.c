#include "hash_tables.h"

void hash_node_delete(hash_node_t *node);

/**
 * hash_table_delete - Deletes a hash table.
 * @ht: A pointer to a hash table.
 */
void hash_table_delete(hash_table_t *ht)
{
	unsigned long int i;

	if (ht == NULL)
		return;

	for (i = 0; i < ht->size; i++)
	{
		if (ht->array[i] != NULL)
			hash_node_delete(ht->array[i]);
	}
	free(ht->array);
	free(ht);
}

/**
 * hash_node_delete - Deletes a hash node.
 * @node: A pointer to a hash node.
 */
void hash_node_delete(hash_node_t *node)
{
	hash_node_t *tmp;

	for (; node; node = tmp)
	{
		tmp = node->next;
		free(node->value);
		free(node->key);
		free(node);
	}
}
