#include "main.h"

/**
 * getc_command - to get command from user
 * @str: user input
 * @c_command: pointer to command
 * @cmd_size: pointer to size of command
 * Return: void
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
void getc_command(char *str, char **c_command, int *cmd_size)
{
	int i = 0, j = 0;

	while (str[i] == 2 || str[i] == ' ')
	{
		i++;
	}
	while (str[i])
	{
		if (str[i] == '\n')
		{
			if (str[i + 1] != '\n')
			{
				str[i] = 2;
				break;
			}
			else
			{
				str[i] = 2;
				i++;
			}
		}
		else if (str[i] == ' ' && !last_space(str + i))
			break;

		else if (str[i] == ' ' && str[i + 1] == ' ')
		{
			i++;
			continue;
		}
		else
			getc_command_helper(str, c_command, cmd_size, &i, &j);
	}
	(*c_command)[j] = '\0';
	alias_replace(c_command, cmd_size);
	edit_command(c_command, cmd_size);
}
/**
 * last_space - check if last char in string is space
 * @str: string to check (char *)
 * Return: (1) if last char in string is space, (0) others (int)
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
int last_space(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i++] != ' ')
			return (1);
	}
	return (0);
}
/**
 * getc_command_helper - helper function
 * @str: user input
 * @c_command: pointer to command
 * @cmd_size: pointer to size of command
 * @i: pointer to index of user input
 * @j: pointer to index of command
 * Return: void
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
void getc_command_helper(char *str, char **c_command,
						 int *cmd_size, int *i, int *j)
{
	if (*j < *cmd_size - 2)
	{
		(*c_command)[*j] = str[*i];
		str[*i] = 2;
		*i += 1;
		*j += 1;
	}
	else
	{
		*c_command = _realloc(*c_command, *cmd_size * 2);
		*cmd_size *= 2;
		buffers(NULL, c_command, 1);
	}
}
/**
 * edit_command - edit command to replace symbols
 * @str_ptr: pointer to command
 * @str_size: pointer to size of command
 * Return: void
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
void edit_command(char **str_ptr, int *str_size)
{
	int i = 0;
	int temp_size = *str_size;
	char *temp = malloc(temp_size);
	char *str = *str_ptr;

	for (i = 0; str[i]; i++)
	{
		if (_strcmp(str + i, "$$") == 0)
		{
			char pid[255];

			nts(getpid(), pid);

			str = replaceTxtInd(str_ptr, pid, i, i + 1);
			i += _strlen(pid) - 1;
		}
		else if (_strcmp(str + i, "$?") == 0)
		{
			char last_exit_code[255];

			nts(State, last_exit_code);

			str = replaceTxtInd(str_ptr, last_exit_code, i, i + 1);
			i += _strlen(last_exit_code) - 1;
		}
		else if (str[i] == '$' && str[i + 1] != '$' &&
				 str[i + 1] != ' ' && str[i + 1])
		{
			edit_command_helper(str_ptr, &str, temp, &i);
		}
		else if (str[i] == '#')
		{
			if ((i && str[i - 1] == ' ') || !i)
				str[i] = '\0';
			break;
		}
	}
	_Free(temp);
}
/**
 * edit_command_helper - helper function to replace
 * @str_ptr: pointer to command
 * @str: pointer to command
 * @temp: pointer to temp string
 * @index: pointer to index of command
 * Return: void
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
void edit_command_helper(char **str_ptr,
						 char **str, char *temp, int *index)
{
	char *value;
	int j = 0, i = *index;

	while ((*str)[i + j] && (*str)[i + j] != ' ')
		j++;
	_memcopy(temp, (*str) + i + 1, j - 1);
	temp[j - 1] = '\0';
	value = get_env_value(temp);
	if (value)
	{
		*str = replaceTxtInd(str_ptr, value, i, i + j - 1);
		*index += _strlen(value) - 1;
		_Free(value);
	}
	else
	{
		*str = replaceTxtInd(str_ptr, " ", i, i + j - 1);
	}
}
