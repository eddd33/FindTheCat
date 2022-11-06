#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

int FLAG_SIZE = 0;

char *hereorbefore(char *mot, int index)
{
    char *copy = strdup(mot);
    copy[index] = '\0';
    return copy;
}
char *hereorafter(char *mot, int index)
{
    return mot + index;
}

// q3
int taille(char *nom)
{
    FILE *fichier = NULL;      // pointeur sur le fichier
    fichier = fopen(nom, "r"); // ouverture du fichier en lecture
    int size = 0;
    if (fichier != NULL)
    {
        fseek(fichier, 0, SEEK_END); // on lit le fichier jusqu'à la fin
        size = ftell(fichier);       // on récupère la position du curseur
        // printf("Taille du fichier : %d octets");
        return size;
        fclose(fichier);
    }
    return 0;
}

bool comparaison(char *nom, char *fichier)
{
    char signe = nom[0];
    char unité = nom[-1];
    char *tamp;
    tamp = nom+1;
    printf("1. %s\n",tamp);
    tamp[strlen(tamp)-1]='\0';
    printf("2. %s\n",tamp);
    



    
    // for (size_t i = 1; i < strlen(nom)-1; i++)
    //{
    //  tamp[i-1] = nom[i];
    //}

    int target = atoi(tamp);
    if (signe == '+')
    {
        if (unité == 'c')
        {
            if (target < taille(fichier))
            {
                //free(tamp);
                return true;
            }
        }
        if (unité == 'k')
        {
            target = target * 1024;
            if (target < taille(fichier))
            {
                //free(tamp);
                return true;
            }
        }
        if (unité == 'M')
        {
            target = target * 1024 * 1024;
            if (target < taille(fichier))
            {
                //free(tamp);
                return true;
            }
        }
        if (unité == 'G')
        {
            target = target * 1024 * 1024 * 1024;
            if (target < taille(fichier))
            {
                //free(tamp);
                return true;
            }
        }
        //free(tamp);
        return false;
    }
    if (signe == '-')
    {
        if (unité == 'c')
        {
            if (target > taille(fichier))
            {
                //free(tamp);
                return true;
            }
        }
        if (unité == 'k')
        {
            target = target * 1024;
            if (target > taille(fichier))
            {
                //free(tamp);
                return true;
            }
        }
        if (unité == 'M')
        {
            target = target * 1024 * 1024;
            if (target > taille(fichier))
            {
                //free(tamp);
                return true;
            }
        }
        if (unité == 'G')
        {
            target = target * 1024 * 1024 * 1024;
            if (target > taille(fichier))
            {
                //free(tamp);
                return true;
            }
        }
        //free(tamp);
        return false;
    }
    return false;
}

void listdir(const char *name, int indent, char *valsize, char *valname)
{
    DIR *dirp;         // pointeur de répertoire
    struct dirent *dp; // pointeur de fichier

    if (!(dirp = opendir(name))) // ouvre le repertoire
        return;

    while ((dp = readdir(dirp)) != NULL) // tant qu'il y a des fichiers
    {
        if (dp->d_type == DT_DIR) // si c'est un répertoire (DT_DIR est le type répertoire)
        {
            char path[1024];                                                   // création d'un chemin
            if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) // si c'est le répertoire courant ou le répertoire parent
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, dp->d_name); // on concatène le chemin du répertoire courant avec le nom du répertoire
            printf("%*s[%s]\n", indent, "", dp->d_name);             // on affiche le nom du répertoire
            listdir(path, indent + 2, valsize, valname);             // on appelle la fonction récursivement
        }
        else // si c'est un fichier
        {
            if (FLAG_SIZE == 1)
            {
                if (comparaison(valsize, dp->d_name) == true)
                {
                    printf("%*s- %s\n", indent, "", dp->d_name); // on affiche le nom du fichier
                }
                // printf("%*s- %s\n", indent, "", dp->d_name); //on affiche le nom du fichier
                // taille(dp->d_name);
            }
        }
        
    }
    closedir(dirp); // on ferme le répertoire
}

int main(int argc, char *argv[])
{

    int size = strlen(*argv);
    char *valsize = NULL;
    char *valname = NULL;
    for (int i = 0; i < size; i++)
    {
        if (strcmp(argv[i], "-test") == 0)
        {
            printf("La valeur du flag %s est %s.\n", argv[i + 1], argv[i + 2]);
            break;
        };
        if (strcmp(argv[i], "-size") == 0)
        {
            FLAG_SIZE = 1;
            valsize = argv[i + 1];
            break;
        };
        if (strcmp(argv[i], "-name") == 0)
        {
            valname = argv[i + 1];
            break;
        }
    }
    listdir(".", 0, valsize, valname);

    return 0;
}

/* bool in(char* list[],char* str){
    int size = strlen(list);
    for (int i = 0; i < size; i++){
        if (list[i]==str){
            return true;
            break;
        }
    }
}
*/

