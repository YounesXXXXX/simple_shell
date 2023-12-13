#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(xinfo_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		xclear_info(info);
		if (xinteractive(info))
			_xputs("$ ");
		_xeputchar(BUF_FLUSH);
		r = xget_input(info);
		if (r != -1)
		{
			xset_info(info, av);
			builtin_ret = xfind_builtin(info);
			if (builtin_ret == -1)
				xfind_cmd(info);
		}
		else if (xinteractive(info))
			_putchar('\n');
		xfree_info(info, 0);
	}
	xwrite_history(info);
	xfree_info(info, 1);
	if (!xinteractive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * xfind_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int xfind_builtin(xinfo_t *info)
{
	int i, built_in_ret = -1;
	xbuiltin_table builtintbl[] = {
		{"exit", _xmyexit},
		{"env", _xmyenv},
		{"help", _xmyhelp},
		{"history", _xmyhistory},
		{"setenv", _xmysetenv},
		{"unsetenv", _xmyunsetenv},
		{"cd", _xmycd},
		{"alias", _xmyalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_xstrcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * xfind_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void xfind_cmd(xinfo_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!xis_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = xfind_path(info, _xgetenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		xfork_cmd(info);
	}
	else
	{
		if ((xinteractive(info) || _xgetenv(info, "PATH=")
			|| info->argv[0][0] == '/') && xis_cmd(info, info->argv[0]))
			xfork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			xprint_error(info, "not found\n");
		}
	}
}

/**
 * xfork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void xfork_cmd(xinfo_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, xget_environ(info)) == -1)
		{
			xfree_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				xprint_error(info, "Permission denied\n");
		}
	}
}
