#ifndef BASH_H
#define BASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void del_space(char *);
void cmd_parse(char *, char ***);

#endif
