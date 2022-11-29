#include "ftc.h"
#include "MegaMimes.h"

int FLAG_SIZE = 0;
int FLAG_NAME = 0;
int FLAG_DATE = 0;
int FLAG_MIME = 0;

// q5
bool dernier_acces(char *nom, char *fichier)
{
    char signe;
    char unité = nom[strlen(nom) - 1];
    char *tamp;
    if (nom[0] == '+')
    {
        signe = nom[0];
        tamp = strdup(nom);
        tamp = tamp + 1;

        tamp[strlen(nom) - 2] = '\0';
    }
    else
    {
        tamp = strdup(nom);
        tamp[strlen(nom) - 1] = '\0';
    }

    struct stat st;
    stat(fichier, &st);
    time_t last = st.st_atime; // temps écoulé depuis le dernier accès

    time_t t = time(NULL); // time_t type donnant en secondes le temps écoulé depuis le 1er janvier 1970

    double diff = difftime(t, last); // différence entre le temps actuel et le dernier accès
    if (signe == '+')
    {
        if (unité == 'm')
        {
            if (diff > atoi(tamp) * 60)
            {
                free(tamp - 1);
                return true;
            }
        }
        else if (unité == 'h')
        {
            if (diff > atoi(tamp) * 3600)
            {
                free(tamp - 1);
                return true;
            }
        }
        else if (unité == 'j')
        {
            if (diff > atoi(tamp) * 86400)
            {
                free(tamp - 1);
                return true;
            }
        }
        free(tamp - 1);
        return false;
    }
    else
    {
        if (unité == 'm')
        {
            if (diff <= atoi(tamp) * 60)
            {
                free(tamp);
                return true;
            }
        }
        else if (unité == 'h')
        {
            if (diff <= atoi(tamp) * 3600)
            {
                free(tamp);
                return true;
            }
        }
        else if (unité == 'j')
        {
            if (diff <= atoi(tamp) * 86400)
            {
                free(tamp);
                return true;
            }
        }
        free(tamp);
        return false;
    }

    free(tamp - 1);
    return false;
}

// q3
unsigned long taille(char *fichier)
{
    struct stat st;
    stat(fichier, &st);
    return st.st_size;
}

bool compar_size(char *nom, char *fichier)
{

    char signe;
    char unité = nom[strlen(nom) - 1];
    char *tamp;

    if (nom[0] == '+' || nom[0] == '-')
    {
        signe = nom[0];
        tamp = strdup(nom);
        tamp = tamp + 1;

        tamp[strlen(nom) - 2] = '\0';
    }
    else
    {
        tamp = strdup(nom);
        tamp[strlen(nom) - 1] = '\0';
    }

    unsigned long target = atoi(tamp);
    if (signe == '+')
    {
        if (unité == 'c')
        {
            if (target < taille(fichier))
            {
                free(tamp - 1);
                return true;
            }
        }
        if (unité == 'k')
        {
            target = target * 1024;
            if (target < taille(fichier))
            {
                free(tamp - 1);
                return true;
            }
        }
        if (unité == 'M')
        {
            target = target * 1024 * 1024;
            if (target < taille(fichier))
            {
                free(tamp - 1);
                return true;
            }
        }
        if (unité == 'G')
        {
            target = target * 1024 * 1024 * 1024;
            if (target < taille(fichier))
            {
                free(tamp - 1);
                return true;
            }
        }
        free(tamp - 1);
        return false;
    }
    else if (signe == '-')
    {
        if (unité == 'c')
        {
            if (target > taille(fichier))
            {
                free(tamp - 1);
                return true;
            }
        }
        if (unité == 'k')
        {
            target = target * 1024;
            if (target > taille(fichier))
            {
                free(tamp - 1);
                return true;
            }
        }
        if (unité == 'M')
        {
            target = target * 1024 * 1024;
            if (target > taille(fichier))
            {
                free(tamp - 1);
                return true;
            }
        }
        if (unité == 'G')
        {
            target = target * 1024 * 1024 * 1024;
            if (target > taille(fichier))
            {
                free(tamp - 1);
                return true;
            }
        }
        free(tamp - 1);
        return false;
    }
    else
    {
        if (unité == 'c')
        {
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
                free(tamp - 1);
                return true;
            }
        }
        if (unité == 'M')
        {
            target = target * 1024 * 1024;
            if (target == taille(fichier))
            {
                free(tamp - 1);
                return true;
            }
        }
        if (unité == 'G')
        {
            target = target * 1024 * 1024 * 1024;
            if (target == taille(fichier))
            {
                free(tamp - 1);
                return true;
            }
        }
        free(tamp);
        return false;
    }
    free(tamp - 1);
    return false;
}

bool compar_name(char *nom, char *fichier)
{

    regex_t regex;
    int ret;

    ret = regcomp(&regex, nom, 0);
    if (ret != 0)
        return false;

    ret = regexec(&regex, fichier, 0, NULL, 0);
    if (ret != 0){
        regfree(&regex);
        return false;
    }
    else{
        regfree(&regex);
        return true;
    }
}

char* get_ext(char *filename){
    char* extension=strrchr(filename, '.');
    if (extension!=NULL && extension !='.'){
        extension=extension+1;
    }
    return extension;
}

void listdir(const char *name, char *valsize, char *valname, char *valdate)
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
            // printf("%s\n", dp->d_name);             // on affiche le nom du répertoire
            listdir(path, valsize, valname, valdate); // on appelle la fonction récursivement
        }
        else // si c'est un fichier
        {
            int test_valide = 1;

            if (FLAG_SIZE == 1)
            {
                if (compar_size(valsize, dp->d_name) == false)
                {
                    test_valide = 0;
                }
            }
            if (FLAG_NAME == 1)
            {

                if (compar_name(valname, dp->d_name) == false)
                {
                    test_valide = 0;
                }
            }
            if (FLAG_DATE == 1)
            {
                if (dernier_acces(valdate, dp->d_name) == false)
                {
                    test_valide = 0;
                }
            }
            if (FLAG_MIME ==1)
            {
                break;
            }
            if (test_valide == 1)
            {
                printf("%s/%s\n", name, dp->d_name); // on affiche le nom du fichier
            }
        }
    }
    closedir(dirp); // on ferme le répertoire
}

int main(int argc, char *argv[])
{

    int size = strlen(*argv);
    char *valsize = "ini";
    char *valname = "ini";
    char *valdate = "ini";

    int i = 0;
    while (argv[i] != '\0')
    {

        if (strcmp(argv[i], "-test") == 0)
        {
            printf("La valeur du flag %s est %s.\n", argv[i + 1], argv[i + 2]);
        };
        if (strcmp(argv[i], "-size") == 0)
        {
            FLAG_SIZE = 1;
            valsize = argv[i + 1];
        };
        if (strcmp(argv[i], "-name") == 0)
        {
            FLAG_NAME = 1;
            valname = argv[i + 1];
        }
        if (strcmp(argv[i], "-date") == 0)
        {
            FLAG_DATE = 1;
            valdate = argv[i + 1];
        }
        if (strcmp(argv[i], "-mime") == 0)
        {
            FLAG_MIME = 1;

        }
        i++;
    }

    listdir(argv[1], valsize, valname, valdate);
    return 0;
}


//how to get the mime type