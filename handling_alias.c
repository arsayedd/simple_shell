#include "main.h"

/**
 * handle_alias - to handle alias command
 * @arguments: arguments to handle
 * Return: 0 (success), 1 (failure)
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
int handle_alias(char **arguments)
{
	int state = 0;
	int i = 0;

	if (arguments[1] && arguments[1][0])
	{
		while (arguments[++i])
			if (_strchr(arguments[i], '='))
			{
				_alias(arguments[i], 1);
			}
			else
			{
				state = print_one_Alias(arguments[i]);
			}
	}
	else
	{
		state = print_All_Alias();
	}
	arguments_free(arguments);
	return (state);
}
/**
 * print_one_Alias - to print an alias
 * @key: key to use
 * Return: 0 (success), 1 (failure)
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
int print_one_Alias(char *key)
{

	int i = 0;
	char **alias_lisr = Alias_list;

	if (alias_lisr && key)
		while (alias_lisr[i])
		{
			if (_strstr(alias_lisr[i], key) == alias_lisr[i] &&
				alias_lisr[i][_strlen(key)] == '=')
			{
				char *str = _strdup(alias_lisr[i]);
				char *ptr = _strstr(str, "=");
				*ptr = '\0';
				print(STDOUT_FILENO, str, "='", ptr + 1, "'\n", NULL);
				_Free(str);
				return (0);
			}
			i++;
		}
	return (0);
}
/**
 * get_alias_value - to get the value of an alias
 * @key: key to use
 * Return: the value of an alias
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
char *get_alias_value(char *key)
{
	char *path = NULL;
	char *cur_env = NULL;
	char *value = NULL;
	int i = 0;
	char **alias_list = Alias_list;

	if (key && *key && alias_list)
	{
		path = _strdup(key);
		path = _realloc(path, _strlen(path) + 2);
		_strcat(path, "=");

		while (alias_list[i])
		{
			cur_env = alias_list[i];
			if (_strstr(cur_env, path) == cur_env)
			{
				value = _strdup(cur_env + _strlen(path));
				_Free(path);
				return (value);
			}
			i++;
		}
	}
	_Free(path);
	return (value);
}
/**
 * get_alias_index - to get the index of an alias
 * @key: key to use
 * Return: the index of an alias
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
int get_alias_index(char *key)
{
	char *path = NULL;
	char *cur_env = NULL;
	int i = 0;
	char **alias_list = Alias_list;

	if (key && *key && alias_list)
	{
		path = _strdup(key);
		path = _realloc(path, _strlen(path) + 2);
		_strcat(path, "=");

		while (alias_list[i])
		{
			cur_env = alias_list[i];
			if (_strstr(cur_env, path) == cur_env)
			{
				_Free(path);
				return (i);
			}
			i++;
		}
	}
	_Free(path);
	return (-1);
}
/**
 * alias_replace - to replace the alias in command
 * @str_ptr: pointer to command
 * @str_size: pointer to size of command
 * Return: void
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
void alias_replace(char **str_ptr, int *str_size)
{
	int i = 0;
	char *temp = _malloc(*str_size);
	char *str = *str_ptr;
	char *value = NULL;

	while (1)
	{
		i = 0;
		while (str[i] && str[i] != ' ')
			i++;
		_memcopy(temp, str, i);
		temp[i] = '\0';
		value = get_alias_value(temp);
		if (value)
		{
			str = replaceTxtInd(str_ptr, value, 0, i - 1);
			_Free(value);
		}
		else
		{
			break;
		}
	}
	_Free(temp);
}
