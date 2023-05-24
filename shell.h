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

/* builtin1.c */
void execute_ls_command(int numwords, char **tokens);

/* Errors */
void display_error(const char *message);
void handle_unrecognized_command(char *tokens[]);

/* Environment.c */
int my_environ(char *details);

/* Pars */
int command_check(const char *command);

/* Path */
void print_error(const char *message);
void check_executable(const char *program_path, char *const *argv);
void search_program(const char *program_name, const char *path_env, 
		char *const *argv)

/* getline.c */
ssize_t read_buf(char *buffer, size_t *buffer_index, 
		size_t *buffer_size, FILE *stream);
int realloc_line(char **line, size_t *n);
ssize_t get_line(char **line, size_t *n, FILE *stream);

/* Strings */
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *getenvr(const char *name, char *env[]);

/* Shell prompt */
void execute_ls_command(int numwords, char **tokens);
void exit_shell(void);
void execute_command(char *cmd_path, char **tokens, char **env);

#endif
