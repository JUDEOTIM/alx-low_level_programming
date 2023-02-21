#include "hash_tables.h"

/**
 * hash_table_print - Prints a hash table.
 * @ht: A pointer to the hash table to print.
 *
 * Description: Key/value pairs are printed in the order
 *              they appear in the array of the hash table.
 */
void hash_table_print(const hash_table_t *ht)
{
	unsigned long int i = 0, flag = 0;
	hash_node_t *node;

	if (ht == NULL)
		return;

	printf("{");
	while (i < ht->size)
	{
		if (ht->array[i] != NULL)
		{
			if (flag)
				printf(", ");

			node = ht->array[i];
			while (node)
			{
				printf("'%s': '%s'", node->key, node->value);
				if (node->next)
					printf(", ");
				node = node->next;
			}
			flag = 1;
		}
		i++;
	}
	printf("}\n");
}
