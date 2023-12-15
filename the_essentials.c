#include "main.h"

/**
 * _free - to free a pointer and set its value to NULL
 * @ptr: pointer to free
 * Return: void
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
void _free(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

/**
 * _malloc - to allocate memory
 * @size: size of memory
 * Return: pointer to the allocated memory
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
void *_malloc(unsigned int size)
{
	void *str = malloc(size);

	if (!str)
	{
		_Free(str);
		print(STDOUT_FILENO, "./hsh :malloc failed\n", NULL);
		exit(-1);
	}
	intail_NULL(str, size);
	return (str);
}

/**
 * _realloc - to reallocate memory
 * @ptr: pointer to the reallocated memory
 * @new_size: new size of memory to be allocated
 * Return: pointer to reallocated memory
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
void *_realloc(void *ptr, int new_size)
{
	void *temp;

	if (new_size < _strlen(ptr))
	{
		_Free(ptr);
		return (NULL);
	}
	temp = _malloc(new_size);
	_memcopy(temp, ptr, _strlen(ptr));
	_Free(ptr);
	return (temp);
}

/**
 * _read - to read from file descriptor
 * @fd: file descriptor to use
 * @str: buffer to use
 * @str_size: size of buffer to use
 * Return: number of characters
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
int _read(int fd, char *str, int str_size)
{
	int read_chars = 0;

	read_chars = read(fd, str, str_size);
	if ((str)[read_chars - 1] == '\n')
		(str)[read_chars - 1] = '\0';
	if (read_chars == -1)
	{
		_Free(str);
		exit(2);
	}
	return (read_chars);
}

/**
 * print - to print to the file descriptor
 * @fd: file descriptor use
 * Return: void
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
void print(int fd, ...)
{
	va_list args;
	char *c_arg, *str = NULL;
	int write_to = 0;

	va_start(args, fd);
	write_to = fd;
	c_arg = va_arg(args, char *);
	str = _strdup(c_arg);
	c_arg = va_arg(args, char *);
	while (c_arg)
	{
		str = _realloc(str, _strlen(str) + _strlen(c_arg) + 1);
		_strcat(str, c_arg);
		c_arg = va_arg(args, char *);
	}
	write(write_to, str, _strlen(str));
	_Free(str);
	va_end(args);
}
