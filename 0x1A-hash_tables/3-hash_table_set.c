#include "hash_tables.h"


/**
 * hash_table_set - Add or update an element in a hash table.
 * @ht: A pointer to the hash table.
 * @key: The key to add - cannot be an empty string.
 * @value: The value associated with key.
 *
 * Return: If it succeeds - 1.
 *         Otherwise - 0.
 */
int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
	unsigned long int key_idx;
	char *value_cpy;
	hash_node_t *newNode, *exist_node;

	if (!ht || !key || !value || *key == '\0')
		return (0);

	value_cpy = strdup(value);
	if (!value_cpy)
		return (0);

	key_idx = key_index((const unsigned char *)key, ht->size);
	exist_node = ht->array[key_idx];
	for (; exist_node; exist_node = exist_node->next)
	{
		if (strcmp(exist_node->key, key) == 0)
		{
			free(exist_node->value);
			exist_node->value = value_cpy;
			return (1);
		}
	}
	newNode = malloc(sizeof(hash_node_t));
	if (newNode == NULL)
	{
		free(value_cpy);
		return (0);
	}
	newNode->value = value_cpy;
	newNode->key = strdup(key);
	if (!(newNode->key))
	{
		free(newNode);
		free(value_cpy);
		return (0);
	}
	newNode->next = ht->array[key_idx];
	ht->array[key_idx] = newNode;
	return (1);
}
