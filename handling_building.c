#include "main.h"

/**
 * handle_builtin - to handle the built-in command
 * @first_sigment: pointer to first sigment
 * @arguments: pointer to array
 * Return: 0 (success), 1 (failure)
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
int handle_builtin(char *first_sigment, char **arguments)
{

	if (_strcmp(first_sigment, "exit") == 0)
	{
		return (handle_exit(arguments));
	}
	else if (_strcmp(first_sigment, "cd") == 0)
	{
		return (handle_cd(arguments));
	}
	else if (_strcmp(first_sigment, "env") == 0)
	{
		arguments_free(arguments);
		return (handle_env(Environment));
	}
	else if (_strcmp(first_sigment, "setenv") == 0)
	{
		return (handle_setenv(arguments));
	}
	else if (_strcmp(first_sigment, "unsetenv") == 0)
	{
		return (handle_unsetenv(arguments));
	}
	else if (_strcmp(first_sigment, "alias") == 0)
	{
		return (handle_alias(arguments));
	}
	else if (_strcmp(first_sigment, "help") == 0)
	{
		arguments_free(arguments);
		print(STDOUT_FILENO, "RTFM: Read the fucking manual!\n", NULL);
		return (0);
	}
	else
	{
		return (0);
	}
}
/**
 * check_builtin - to check wether the command is built-in
 * @first_sigment: pointer to first sigment
 * Return: 1 (built-in), otherwise 0
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
int check_builtin(char *first_sigment)
{
	char *arr[] = {"exit", "cd", "env", "setenv", "unsetenv", "alias",
				   "help", NULL};
	int i;

	for (i = 0; arr[i]; i++)
	{
		if (_strcmp(first_sigment, arr[i]) == 0)
			return (1);
	}
	return (0);
}
