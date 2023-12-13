#include "shell.h"

/**
 * _xmyexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _xmyexit(xinfo_t *info)
{
	int exitcheck;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = _xerratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			xprint_error(info, "Illegal number: ");
			_xeputs(info->argv[1]);
			_xeputchar('\n');
			return (1);
		}
		info->err_num = _xerratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _xmycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _xmycd(xinfo_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_xputs("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _xgetenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _xgetenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_xstrcmp(info->argv[1], "-") == 0)
	{
		if (!_xgetenv(info, "OLDPWD="))
		{
			_xputs(s);
			_putchar('\n');
			return (1);
		}
		_xputs(_xgetenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _xgetenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		xprint_error(info, "can't cd to ");
		_xeputs(info->argv[1]), _xeputchar('\n');
	}
	else
	{
		_xsetenv(info, "OLDPWD", _xgetenv(info, "PWD="));
		_xsetenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _xmyhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _xmyhelp(xinfo_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_xputs("help call works. Function not yet implemented \n");
	if (0)
		_xputs(*arg_array); /* temp att_unused workaround */
	return (0);
}
