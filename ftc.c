#include "ftc.h"
#include "MegaMimes.h"

int FLAG_SIZE = 0;
int FLAG_NAME = 0;
int FLAG_DATE = 0;
int FLAG_MIME = 0;
int FLAG_NOOPTION = 0;
int FLAG_TEST = 0;
char* STARTING_POINT;

// q5
bool dernier_acces(char *nom, char *fichier)
{
    char signe;
    char unit = nom[strlen(nom) - 1];
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
        if (unit == 'm')
        {
            if (diff > atoi(tamp) * 60)
            {
                free(tamp - 1);
                return true;
            }
        }
        else if (unit == 'h')
        {
            if (diff > atoi(tamp) * 3600)
            {
                free(tamp - 1);
                return true;
            }
        }
        else if (unit == 'j')
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
        if (unit == 'm')
        {
            if (diff <= atoi(tamp) * 60)
            {
                free(tamp);
                return true;
            }
        }
        else if (unit == 'h')
        {
            if (diff <= atoi(tamp) * 3600)
            {
                free(tamp);
                return true;
            }
        }
        else if (unit == 'j')
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

    unsigned long filesize = st.st_size;
    // printf("%lu %s\n",filesize, fichier);
    return filesize;
}

bool compar_size(char *nom, char *fichier)
{

    char signe;
    char unit = nom[strlen(nom) - 1];
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
        if (unit == 'c')
        {
            if (target < taille(fichier))
            {
                free(tamp - 1);
                return true;
            }
        }
        if (unit == 'k')
        {
            target = target * 1024;
            if (target < taille(fichier))
            {
                free(tamp - 1);
                return true;
            }
        }
        if (unit == 'M')
        {
            target = target * 1024 * 1024;
            if (target < taille(fichier))
            {
                free(tamp - 1);
                return true;
            }
        }
        if (unit == 'G')
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
        if (unit == 'c')
        {
            if (target > taille(fichier))
            {
                free(tamp - 1);
                return true;
            }
        }
        if (unit == 'k')
        {
            target = target * 1024;
            if (target > taille(fichier))
            {
                free(tamp - 1);
                return true;
            }
        }
        if (unit == 'M')
        {
            target = target * 1024 * 1024;
            if (target > taille(fichier))
            {
                free(tamp - 1);
                return true;
            }
        }
        if (unit == 'G')
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
        if (unit == 'c')
        {
            if (target == taille(fichier))
            {
                free(tamp);
                return true;
            }
        }
        if (unit == 'k')
        {
            target = target * 1024;
            if (target == taille(fichier))
            {
                free(tamp - 1);
                return true;
            }
        }
        if (unit == 'M')
        {
            target = target * 1024 * 1024;
            if (target == taille(fichier))
            {
                free(tamp - 1);
                return true;
            }
        }
        if (unit == 'G')
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

    ret = regcomp(&regex, nom, REG_EXTENDED);
    if (ret != 0)
        return false;

    ret = regexec(&regex, fichier, 0, NULL, 0);
    if (ret != 0)
    {
        regfree(&regex);
        return false;
    }
    else
    {
        regfree(&regex);
        return true;
    }
}

char *get_ext(char *filename)
{
    char *extension = strrchr(filename, '.');
    if (extension != NULL && extension != '.')
    {
        extension = extension + 1;
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

        int test_valide = 1;
        if (dp->d_type == DT_DIR) // si c'est un répertoire (DT_DIR est le type répertoire)
        {
            char path[1024];                                                   // création d'un chemin
            if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) // si c'est le répertoire courant ou le répertoire parent
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, dp->d_name); // on concatène le chemin du répertoire courant avec le nom du répertoire

            if (FLAG_NOOPTION == 1)
            {
                printf("%s/%s\n", name, dp->d_name);
            }
            // on affiche le nom du répertoire
            listdir(path, valsize, valname, valdate); // on appelle la fonction récursivement
        }
        else // si c'est un fichier
        {

            if (FLAG_SIZE == 1)
            {
                char *temp[1024];
                snprintf(temp, sizeof(temp), "%s/%s", name, dp->d_name);
                if (compar_size(valsize, temp) == false)
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
                char *temp[1024];
                snprintf(temp, sizeof(temp), "%s/%s", name, dp->d_name);
                if (dernier_acces(valdate, temp) == false)
                {
                    test_valide = 0;
                }
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

    if (argv[2] == '\0')
    {
        FLAG_NOOPTION = 1;
        printf("%s\n", argv[1]);
    }
    else
    {
        while (argv[i] != NULL)
        {

            if (strcmp(argv[i], "-test") == 0)
            {
                FLAG_TEST = 1;
                if (strcmp(argv[i + 1], "-test") != 0 && strcmp(argv[i + 1], "-name") != 0 && strcmp(argv[i + 1], "-size") != 0 && strcmp(argv[i + 1], "-date") != 0 && strcmp(argv[i + 1], "-mime") != 0 && strcmp(argv[i + 1], "-ctc") != 0 && strcmp(argv[i + 1], "-dir") != 0 && strcmp(argv[i + 1], "-color") != 0 && strcmp(argv[i + 1], "-perm") != 0 && strcmp(argv[i + 1], "-link") != 0 && strcmp(argv[i + 1], "-threads") != 0 && strcmp(argv[i + 1], "-ou") != 0)
                {
                    printf("Le flag %s n'est pas correct\n", argv[i + 1]);
                }
                else if (argv[i + 1] == '\0')
                {
                    printf("Le flag %s n'est pas correct\n", argv[i + 1]);
                }
                else
                {
                    printf("La valeur du flag %s est %s\n", argv[i + 1], argv[i + 2]);
                }
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
    }

    if (FLAG_TEST == 0)
    {
        STARTING_POINT=argv[1];
        if (STARTING_POINT[strlen(STARTING_POINT)-1]=='/'){
            STARTING_POINT[strlen(STARTING_POINT)-1]='\0';
        }
        listdir(STARTING_POINT, valsize, valname, valdate);
    }

    return 0;
}

// how to get the mime type