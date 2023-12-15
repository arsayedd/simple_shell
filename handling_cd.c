#include "main.h"

/**
 * handle_cd - to handle cd command
 * @arguments: pointer to array
 * Return: 0 (success), 1 (failure)
 * This function will only work on Linux.
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
int handle_cd(char **arguments)
{
	char cwd[BUFFER_SIZE];
	char *cd = NULL;
	char **pwd, **oldpwd;

	getcwd(cwd, sizeof(cwd));
	pwd = creat_2D(3, "setenv", "PWD", arguments[1]);
	oldpwd = creat_2D(3, "setenv", "OLDPWD", cwd);

	if (arguments[1] && *arguments[1])
	{
		if (!handle_cd_helper(arguments, pwd, oldpwd, cd, cwd))
			return (0);
	}
	else
	{
		cd = get_env_value("HOME");
		if (cd)
		{
			_Free(pwd[2]);
			pwd[2] = cd;
			chdir(cd);
		}
	}
	handle_setenv(pwd);
	handle_setenv(oldpwd);
	arguments_free(arguments);
	return (0);
}
/**
 * handle_cd_helper - to handle this cd command 
 * @arguments: pointer to array
 * @pwd: pointer to point to array of pwd arguments
 * @oldpwd: pointer to array of previous pwd arguments
 * @cd: pointer of string to the certain place
 * @cwd: pointer of string to the current directory
 * Return: 1 (success), 0 (failure)
 * Authors: Ahmed Raafat & Ahmed Abdelanasser
 */
int handle_cd_helper(char **arguments, char **pwd,
					 char **oldpwd, char *cd, char *cwd)
{
	if (_strcmp(arguments[1], "-") == 0)
	{
		cd = get_env_value("OLDPWD");
		if (cd)
		{
			_Free(pwd[2]);
			pwd[2] = cd;
			chdir(cd);
			getcwd(cwd, sizeof(cwd));
			print(STDOUT_FILENO, cwd, "\n", NULL);
		}
		else
		{
			print(STDOUT_FILENO, cwd, "\n", NULL);
			_Free(oldpwd[2]);
			_Free(pwd[2]);
		}
	}
	else
	{
		if (chdir(arguments[1]) == -1)
		{
			if (errno == ENOENT)
			{
				char *error = "./hsh: 1: cd: can't cd to ";

				print(STDERR_FILENO, error, arguments[1], "\n", NULL);
			}
			else if (errno == EACCES)
			{
				char *error = "./hsh: 1: cd: can't cd to ";

				print(STDERR_FILENO, error, arguments[1], "\n", NULL);
			}
			arguments_free(pwd), arguments_free(oldpwd), arguments_free(arguments);
			return (0);
		}
	}
	return (1);
}
