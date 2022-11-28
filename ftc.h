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


bool isEmpty(liste *liste);
void retire(file *element,liste* linked_list);
liste *list_create();
void liste_destroy(liste *listint);
void ajout_dico(char* fichier, liste *dico);
void element_print(file* fichier);
void liste_print(liste* dico);

bool dernier_acces(char* nom, char* fichier);
int taille(char *nom);
bool compar_size(char *nom, char *fichier);
bool compar_name(char* nom, char* fichier);
void et();
void listdir(const char *name, char *valsize, char *valname, char *valdate);
int main(int argc, char *argv[]);

#endif
