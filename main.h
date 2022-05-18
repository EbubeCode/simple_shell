#ifndef MAIN_H
#define MAIN_H

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <dirent.h>

extern char **environ;

char **split_command(char *command, char *delim);
char **get_path(void);
char *str_concat(char *s1, char *s2);
char *search_path(char *file);
char *_strdup(char *str);
void print_env(void);
int handle_builtin(char **av);
int compare(char *f1, char *f2);


#endif /* MAIN_H */

