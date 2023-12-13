#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for xconvert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} xlist_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	xlist_t *env;
	xlist_t *history;
	xlist_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} xinfo_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(xinfo_t *);
} xbuiltin_table;


/* _shloop.c */
int hsh(xinfo_t *, char **);
int xfind_builtin(xinfo_t *);
void xfind_cmd(xinfo_t *);
void xfork_cmd(xinfo_t *);

/* _parser.c */
int xis_cmd(xinfo_t *, char *);
char *xdup_chars(char *, int, int);
char *xfind_path(xinfo_t *, char *, char *);

/* loophsh.c */
int xloophsh(char **);

/* _errors.c */
void _xeputs(char *);
int _xeputchar(char);
int _xputfd(char c, int fd);
int _xputsfd(char *str, int fd);

/* _string.c */
int _xstrlen(char *);
int _xstrcmp(char *, char *);
char *xstarts_with(const char *, const char *);
char *_xstrcat(char *, char *);

/* _string1.c */
char *_xstrcpy(char *, char *);
char *_xstrdup(const char *);
void _xputs(char *);
int _putchar(char);

/* _exits.c */
char *_xstrncpy(char *, char *, int);
char *_xstrncat(char *, char *, int);
char *_xstrchr(char *, char);

/* _tokenizer.c */
char **xstrtow(char *, char *);
char **xstrtow2(char *, char);

/* _realloc.c */
char *_xmemset(char *, char, unsigned int);
void xffree(char **);
void *_xrealloc(void *, unsigned int, unsigned int);

/* _memory.c */
int xbfree(void **);

/* _atoi.c */
int xinteractive(xinfo_t *);
int xis_delim(char, char *);
int _xisalpha(int);
int _xatoi(char *);

/* _errors1.c */
int _xerratoi(char *);
void xprint_error(xinfo_t *, char *);
int xprint_d(int, int);
char *xconvert_number(long int, int, int);
void xremove_comments(char *);

/* _builtin.c */
int _xmyexit(xinfo_t *);
int _xmycd(xinfo_t *);
int _xmyhelp(xinfo_t *);

/* _builtin1.c */
int _xmyhistory(xinfo_t *);
int _xmyalias(xinfo_t *);

/*_getline.c */
ssize_t xget_input(xinfo_t *);
int _xgetline(xinfo_t *, char **, size_t *);
void xsigintHandler(int);

/* _getinfo.c */
void xclear_info(xinfo_t *);
void xset_info(xinfo_t *, char **);
void xfree_info(xinfo_t *, int);

/* _environ.c */
char *_xgetenv(xinfo_t *, const char *);
int _xmyenv(xinfo_t *);
int _xmysetenv(xinfo_t *);
int _xmyunsetenv(xinfo_t *);
int xpopulate_env_list(xinfo_t *);

/* _getenv.c */
char **xget_environ(xinfo_t *);
int _xunsetenv(xinfo_t *, char *);
int _xsetenv(xinfo_t *, char *, char *);

/* _history.c */
char *xget_history_file(xinfo_t *info);
int xwrite_history(xinfo_t *info);
int xread_history(xinfo_t *info);
int xbuild_history_list(xinfo_t *info, char *buf, int linecount);
int xrenumber_history(xinfo_t *info);

/* _lists.c */
xlist_t *xadd_node(xlist_t **, const char *, int);
xlist_t *xadd_node_end(xlist_t **, const char *, int);
size_t xprint_list_str(const xlist_t *);
int xdelete_node_at_index(xlist_t **, unsigned int);
void xfree_list(xlist_t **);

/* _lists1.c */
size_t xlist_len(const xlist_t *);
char **xlist_to_strings(xlist_t *);
size_t xprint_list(const xlist_t *);
xlist_t *xnode_starts_with(xlist_t *, char *, char);
ssize_t xget_node_index(xlist_t *, xlist_t *);

/* _vars.c */
int xis_chain(xinfo_t *, char *, size_t *);
void xcheck_chain(xinfo_t *, char *, size_t *, size_t, size_t);
int xreplace_alias(xinfo_t *);
int xreplace_vars(xinfo_t *);
int xreplace_string(char **, char *);

#endif
