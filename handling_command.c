#include "main.h"

/**
 * handle_command - to handle any command
 * @command: pointer to command overall
 * Return: void
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
void handle_command(char *command)
{
	char *first_sigment = _strtok2(command, " \t");
	char **arguments = NULL;

	add_args(&arguments, first_sigment);
	while (first_sigment != NULL)
	{
		char *cur_sigment = _strtok2(NULL, " ");

		if (cur_sigment == NULL)
		{
			break;
		}
		else
		{
			char c = check_many_commands(cur_sigment);

			if (c)
			{
				if (handle_command_helper(first_sigment, arguments, c))
					return;
				arguments = NULL;
				first_sigment = _strtok2(NULL, " ");
				if (!first_sigment)
					return;
				add_args(&arguments, first_sigment);
			}
			else
			{
				add_args(&arguments, cur_sigment);
			}
		}
	}
	handle_curCommand(first_sigment, arguments);
}
/**
 * handle_command_helper - to handle a command helper 
 * @first_sigment: pointer to the first sigment
 * @arguments: pointer to array
 * @c: char to use
 * Return: 1 (success), 0 (failure)
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
int handle_command_helper(char *first_sigment, char **arguments, char c)
{
	switch (c)
	{
	case ';':
		handle_curCommand(first_sigment, arguments);
		break;
	case '&':
		handle_curCommand(first_sigment, arguments);
		if (State != 0)
			return (1);
		break;
	case '|':
		handle_curCommand(first_sigment, arguments);
		if (!State)
			return (1);
		break;
	default:
		break;
	}
	return (0);
}
/**
 *  check_many_commands - to check whether the user entered too many commands
 * @str: pointer to string to use
 * Return: ';' if the user entered too many commands, otherwise 0
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */

char check_many_commands(char *str)
{
	if (_strcmp(str, ";") == 0)
	{
		return (';');
	}
	else if (_strcmp(str, "&&") == 0)
	{
		return ('&');
	}
	else if (_strcmp(str, "||") == 0)
	{
		return ('|');
	}
	return (0);
}

/**
 * handle_curCommand - to handle the current command stated
 * @first_sigment: pointer to first sigment
 * @arguments: pointer to array
 * Return: void
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
void handle_curCommand(char *first_sigment, char **arguments)
{
	char *c_path;

	if (_strchr(first_sigment, '/') && access(first_sigment, X_OK) == 0)
	{
		c_path = first_sigment;
		handle_exce(c_path, arguments);
		if (State)
			_state(2);
	}
	else if (check_builtin(first_sigment))
	{
		_state(handle_builtin(first_sigment, arguments));
	}
	else
	{
		char *path = get_path(Environment);

		c_path = find_path(path, first_sigment);
		if (c_path)
		{
			handle_exce(c_path, arguments);
			_Free(c_path);
		}
		else
		{
			_state(handle_error(first_sigment, path));
			arguments_free(arguments);
		}
	}
}
