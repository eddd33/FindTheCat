#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

void listdir(const char *name, int indent)
{
    DIR *dirp; // pointeur de répertoire
    struct dirent *dp;  // pointeur de fichier

    if (!(dirp = opendir(name))) //ouvre le repertoire
        return;

    while ((dp = readdir(dirp)) != NULL) //tant qu'il y a des fichiers
    {
        if (dp->d_type == DT_DIR) //si c'est un répertoire (DT_DIR est le type répertoire)
        {
            char path[1024]; //création d'un chemin
            if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) //si c'est le répertoire courant ou le répertoire parent
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, dp->d_name); //on concatène le chemin du répertoire courant avec le nom du répertoire
            printf("%*s[%s]\n", indent, "", dp->d_name); //on affiche le nom du répertoire
            listdir(path, indent + 2); //on appelle la fonction récursivement
        }
        else
        {
            printf("%*s- %s\n", indent, "", dp->d_name); //on affiche le nom du fichier
        }
    }
    closedir(dirp); //on ferme le répertoire
}

//q3
//void size ()

int main(int argc, char *argv[])
{

    int size = strlen(*argv);
    for (int i = 0; i < size; i++)
    {
        if (strcmp(argv[i], "-test") == 0)
        {
            printf("La valeur du flag %s est %s.\n", argv[i + 1], argv[i + 2]);
            break;
        };
        //if (strcmp(argv[i], "-size") == 0)
        //{
            //size(argv[i + 1]);
          //  break;
        //};"))
    }
    listdir(".",0);

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