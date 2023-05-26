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

#define BUFFER_SIZE 1024

/* Tokenizer */
#define MAX_TOKENS 100

int tokenizer(char *str, const char *delimiters, char *tokens[]);

/* Errors */
void display_error(const char *message);
void handle_unrecognized_command(char *tokens[]);

/* Environment.c */
extern char **environ;
int my_environ(void);

/* Pars */
int command_check(const char *command);

/* getline.c */
ssize_t read_buf(char *buf, size_t *buf_index, size_t *buf_size, FILE *stream);
int realloc_line(char **line, size_t *n);
ssize_t get_line(char **line, size_t *n, FILE *stream);
void prompt(void);

/* Exit.c */
int exit_shell(char **arr);

/* String.c */
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);

/* Path.c */
void check_executable(const char *path, char *argv[]);
void print_error(const char *msg);
void execute_program(const char *program_path, char *argv[]);
int search_program(const char *name, const char *path_env, char *argv[]);

/* Strings */
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *getenvr(const char *name, char *env[]);

#endif
