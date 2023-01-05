#include "main.h"
#include <stdlib.h>

/**
 * read_textfile - Reads a text file and prints it to POSIX stdout.
 * @filename: A pointer to the name of the file.
 * @letters: The number of letters the
 *           function should read and print.
 *
 * Return: If the function fails or filename is NULL - 0.
 *         O/w - the actual number of bytes the function can read and print.
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	ssize_t r, o, w;
	char *buf;

	if (!filename)
		return (0);

	buf = malloc(sizeof(char) * letters);
	if (!buf)
		return (0);

	o = open(filename, O_RDONLY);
	r = read(o, buf, letters);
	w = write(STDOUT_FILENO, buf, r);

	if (o == -1 || r == -1 || w != r)
	{
		free(buf);
		return (0);
	}

	free(buf);

	close(o);

	return (w);
}
