#include "main.h"

/**
 * buffers - to set new values for buffers
 * @all_str: pointer to be set
 * @c_command: pointer to be set
 * @state: state of these buffers
 * Return: void
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
void buffers(char **all_str, char **c_command, int state)
{
	static char **str;
	static char **command;

	if (all_str)
		str = all_str;
	if (c_command)
		command = c_command;
	if (state == 0)
	{
		_Free(*str);
		_Free(*command);
	}
}
/**
 * _enviornment - to set enviornment to the new values
 * @envp: pointer to be set
 * @state: state of this enviornment
 * Return: pointer to this enviornment
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
char ***_enviornment(char **envp, int state)
{
	static char **enviornment;

	if (state && envp)
	{
		enviornment = envp;
	}
	if (!state)
	{
		arguments_free(enviornment);
	}
	return (&enviornment);
}
/**
 * _state - to set state to a new value
 * @c_state: state to use
 * Return: state
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
int _state(int c_state)
{
	static int state;

	if (c_state == Get_state)
	{
		return (state);
	}
	else
	{
		state = c_state;
		return (state);
	}
}
/**
 * _alias - to set new values for alias
 * @alias_arg: alias to use
 * @state: state of this alias
 * Return: pointer to this alias
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
char **_alias(char *alias_arg, int state)
{
	static char **alias_list;

	if (state && alias_arg && _strchr(alias_arg, '='))
	{
		char *temp = NULL;
		char *value = NULL;
		int i = 0;

		while (alias_arg[i] && alias_arg[i] != '=')
			i++;
		temp = _malloc(i + 1);
		_memcopy(temp, alias_arg, i);
		temp[i] = '\0';
		value = get_alias_value(temp);
		if (value)
		{
			i = get_alias_index(temp);
			_Free(alias_list[i]);
			alias_list[i] = _strdup(alias_arg);
			_Free(value);
		}
		else
		{
			add_args(&alias_list, alias_arg);
		}
		_Free(temp);
		return (alias_list);
	}
	else if (state)
	{
		return (alias_list);
	}
	arguments_free(alias_list);
	return (NULL);
}
