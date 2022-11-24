#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>


int FLAG_SIZE = 0;
int FLAG_NAME = 0;
int FLAG_ET = 0;


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

bool compar_size(char *nom, char *fichier)
{

    char signe;
    char unité = nom[strlen(nom)-1];
    char *tamp;
    //printf("signe %c\n",nom[0]);
    if (nom[0]=='+' || nom[0]=='-')
    {
        signe = nom[0];
        tamp=strdup(nom);
        tamp=tamp+1;
        
        tamp[strlen(nom)-2]='\0';
    }
    else
    {
        tamp=strdup(nom);
        tamp[strlen(nom)-1]='\0';
    }
    
    

    int target = atoi(tamp);
    //printf("tamp %s\n",tamp);
    if (signe == '+')
    {
        if (unité == 'c')
        {
            if (target < taille(fichier))
            {
                free(tamp-1);
                return true;
            }
        }
        if (unité == 'k')
        {
            target = target * 1024;
            if (target < taille(fichier))
            {
                free(tamp-1);
                return true;
            }
        }
        if (unité == 'M')
        {
            target = target * 1024 * 1024;
            if (target < taille(fichier))
            {
                free(tamp-1);
                return true;
            }
        }
        if (unité == 'G')
        {
            target = target * 1024 * 1024 * 1024;
            if (target < taille(fichier))
            {
                free(tamp-1);
                return true;
            }
        }
        free(tamp-1);
        return false;
    }
    else if (signe == '-')
    {
        if (unité == 'c')
        {
            if (target > taille(fichier))
            {
                free(tamp-1);
                return true;
            }
        }
        if (unité == 'k')
        {
            target = target * 1024;
            if (target > taille(fichier))
            {
                free(tamp-1);
                return true;
            }
        }
        if (unité == 'M')
        {
            target = target * 1024 * 1024;
            if (target > taille(fichier))
            {
                free(tamp-1);
                return true;
            }
        }
        if (unité == 'G')
        {
            target = target * 1024 * 1024 * 1024;
            if (target > taille(fichier))
            {
                free(tamp-1);
                return true;
            }
        }
        free(tamp-1);
        return false;
    }
    else
    {
        if (unité == 'c')
        {
            //printf("target %d\n",target);
            if (target == taille(fichier))
            {
                free(tamp);
                return true;
            }
        }
        if (unité == 'k')
        {
            target = target * 1024;
            if (target == taille(fichier))
            {
                free(tamp-1);
                return true;
            }
        }
        if (unité == 'M')
        {
            target = target * 1024 * 1024;
            if (target == taille(fichier))
            {
                free(tamp-1);
                return true;
            }
        }
        if (unité == 'G')
        {
            target = target * 1024 * 1024 * 1024;
            if (target == taille(fichier))
            {
                free(tamp-1);
                return true;
            }
        }
        free(tamp);
        return false;
    }
    free(tamp-1);
    return false;
}

bool compar_name(char* nom, char* fichier){
    if (strcmp(nom,fichier)==0){
        return true;
    }
    return false;
}

void et(){
    
}

void listdir(const char *name, char *valsize, char *valname)
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
            //printf("%s\n", dp->d_name);             // on affiche le nom du répertoire
            listdir(path, valsize, valname);             // on appelle la fonction récursivement
        }
        else // si c'est un fichier
        {
        
            if (FLAG_ET > 1){
                et();
            }
            else if (FLAG_SIZE == 1)
            {
                
                if (compar_size(valsize, dp->d_name) == true)
                {   
                    printf("%s/%s\n",name,dp->d_name); // on affiche le nom du fichier
                }

            }
            else if (FLAG_NAME == 1){
                if (compar_name(valname, dp->d_name) == true)
                {   
                    printf("%s/%s\n",name,dp->d_name); // on affiche le nom du fichier
                }
            }
            else {
                printf("%s/%s\n",name,dp->d_name); // on affiche le nom du fichier
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
        //printf("voici l'arg i : %s\n", argv[i]);
        if (strcmp(argv[i], "-test") == 0)
        {
            printf("La valeur du flag %s est %s.\n", argv[i + 1], argv[i + 2]);
            FLAG_ET++;
            break;
        };
        if (strcmp(argv[i], "-size") == 0)
        {
            FLAG_SIZE = 1;
            FLAG_ET++;
            valsize = argv[i + 1];
            break;
        };
        if (strcmp(argv[i], "-name") == 0)
        {
            FLAG_NAME = 1;
            FLAG_ET++;
            valname = argv[i + 1];
            break;
        }
    }
    
    listdir(argv[1],valsize, valname);

    return 0;
}

//how to get the pwd of a repertory in c ?
