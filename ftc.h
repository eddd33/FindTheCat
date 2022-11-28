#ifndef _FTC_H_
#define _FTC_H_

struct liste
{
    file *head;
};
typedef struct liste liste;
struct file
{
    struct file *next;
    struct dirent *d; // pointeur vers le file
};

typedef struct file file;

#endif
