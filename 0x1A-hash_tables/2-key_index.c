#include "hash_tables.h"

/**
 * key_index - Obtain the index which the key/value
 *	       pair should be stored in the array of
 *	       the hash table.
 * @key: The key.
 * @size: Size of the array of the hash table.
 *
 * Return: The index of a key.
 */
unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
	return (hash_djb2(key) % size);
}
