#ifndef _FTC_H_
#define _FTC_H_

struct liste
{
    fichier *head;
};

struct fichier
{
    struct fichier *next;
    struct dirent *d; // pointeur vers le fichier
};

#endif
