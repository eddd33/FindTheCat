#ifndef _FTC_H_
#define _FTC_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <assert.h>
#include <errno.h>
#include <regex.h>


bool dernier_acces(char* nom, char* fichier);
unsigned long taille(char *nom);
bool compar_size(char *nom, char *fichier);
bool compar_name(char* nom, char* fichier);
void listdir(const char *name, char *valsize, char *valname, char *valdate);
int main(int argc, char *argv[]);

#endif
