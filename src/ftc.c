#include "ftc.h"
#include "MegaMimes.h"

int FLAG_SIZE = 0;
int FLAG_NAME = 0;
int FLAG_DATE = 0;
int FLAG_MIME = 0;
bool FLAG_MIMESLASH = false;
int FLAG_NOOPTION = 0;
int FLAG_TEST = 0;
int FLAG_CTC = 0;
int FLAG_DIR = 0;
int FLAG_DIROPTION = 0;
int FLAG_OU=0;
int FLAG_COLOR=0;
int FLAG_PERM=0;
char *STARTING_POINT;

// donne si la condition pour -date est remplie
// nom est le paramètre de -date
// fichier est le fichier à tester
bool dernier_acces(char* nom, char* fichier){
    struct stat st;
    stat(fichier, &st);
    time_t last = st.st_atime; //temps écoulé depuis le dernier accès

    time_t t = time(NULL);//time_t type donnant en secondes le temps écoulé depuis le 1er janvier 1970

    double diff = difftime(t, last); //différence entre le temps actuel et le dernier accès

    if (strcmp(nom, "now")==0){
        if (diff<60){
            return true;
        }
    }
    if (strcmp(nom, "today")==0){
        if (diff<86400){
            return true;
        }
    }
    if (strcmp(nom, "yesterday")==0){
        if (diff<172800 && diff>86400){
            return true;
        }
    }
    if (strcmp(nom, "this month")==0){
        if (diff<2678400){
            return true;
        }
    }

    char signe;
    char unité = nom[strlen(nom)-1];
    char *tamp;
    if (nom[0]=='+')
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

    
    if (signe == '+')
    {
        if(unité == 'm'){
        if(diff > atoi(tamp)*60){
            free(tamp-1);
            return true;
        }
        }
        else if(unité == 'h'){
            if(diff > atoi(tamp)*3600){
                free(tamp-1);
                return true;
            }
        }
        else if(unité == 'j'){
            if(diff > atoi(tamp)*86400){
                free(tamp-1);
                return true;
            }
        }
        free(tamp-1);
        return false;
    }
    
    else
    {
        if(unité == 'm'){
        if(diff <= atoi(tamp)*60){
            free(tamp);
            return true;
        }
        }
        else if(unité == 'h'){
            if(diff <= atoi(tamp)*3600){
                free(tamp);
                return true;
            }
        }
        else if(unité == 'j'){
            if(diff <= atoi(tamp)*86400){
                free(tamp);
                return true;
            }
        }
        free(tamp);
        return false;
    }
    
    
    free(tamp-1);
    return false;
}

// renvoie la taille du fichier
unsigned long taille(char *fichier)
{

    struct stat st;
    stat(fichier, &st);

    unsigned long filesize = st.st_size;
    // printf("%lu %s\n",filesize, fichier);
    return filesize;
}

// donne si la condition pour -size est remplie
// nom est le paramètre de -size
// fichier est le fichier à tester
bool compar_size(char *nom, char *fichier)
{

    char signe ='.'; // on initialise signe
    char unit = nom[strlen(nom) - 1];
    

    char *tamp;

    if (nom[0] == '+' || nom[0] == '-')
    {
        signe = nom[0];
        tamp = strdup(nom);
        tamp = tamp + 1;

        tamp[strlen(nom) - 2] = '\0';
    }
    else if (unit=='c' || unit=='k' || unit=='M' || unit=='G')
    {
        tamp = strdup(nom);
        tamp[strlen(nom) - 1] = '\0';
    }
    else{
        tamp = strdup(nom);
    }

    unsigned long target = atoi(tamp);
    if (signe == '+')
    {
        if (unit!='k' && unit!='M' && unit!='G')
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
        if (unit!='k' && unit!='M' && unit!='G')
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
        if (unit!='k' && unit!='M' && unit!='G')
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

// donne si la condition pour -name est remplie
// nom est le paramètre de -name
// fichier est le fichier à tester
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

// donne si la condition pour -mime est remplie
// valmime est le paramètre de -mime
// fichier est le fichier à tester
bool compar_mime(char *valmime, char *fichier)
{
    char **extensions = getMegaMimeExtensions(valmime);
    // stop if extensions is null
    if (extensions == NULL)
        return false;
    // get extension of fichier
    char *ext = strrchr(fichier, '.');
    if (ext == NULL)
    {
        freeMegaStringArray(extensions);
        return false;
    }
    for (int i = 0; extensions[i] != NULL; i++)
    {
        // printf("%s %s\n", ext,extensions[i]+1);
        if (strcmp(extensions[i] + 1, ext) == 0)
        {
            freeMegaStringArray(extensions);
            return true;
        }
    }

    // returns {'*.mp4', NULL}
    freeMegaStringArray(extensions);
    return false;
}

// donne si la condition pour -ctc est remplie
// nom est le paramètre de -ctc
// fichier est le fichier à tester
bool lecture(char *nom, char *fichier)
{
    FILE *f = fopen(fichier, "r");
    if (f == NULL)
        return false;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, f)) != -1) //lit le fichier ligne par ligne
    {
        if (strstr(line, nom) != NULL) //si la ligne contient le mot recherché
        {
            free(line);
            fclose(f);
            return true;
        }
        if (compar_name(nom, line))//regarde la condition pour le regex
        { 
            return true;
        }
    }
    free(line);
    fclose(f);
    return false;
}
// donne si la condition pour -perm est remplie
// valperm est le paramètre de -perm
// fichier est le fichier à tester
bool compar_perm(char *valperm, char *fichier){
    struct stat st;
    stat(fichier, &st);
    
    mode_t perm = st.st_mode & 0777; //mode_t est un type de données qui contient les permissions du fichier
    //on récupère les permissions du fichier et on les met dans perm
    char *perm_str = malloc(4);
    sprintf(perm_str, "%o", perm);
    
    if (strcmp(perm_str, valperm) == 0){
        free(perm_str);
        return true;
    }
    free(perm_str);
    return false;
}




//listdir est la fonction qui parcourt les fichiers et les répertoires
//et qui appelle les fonctions de comparaison en fonction des paramètres

void listdir(const char *name, char *valsize, char *valname, char *valdate, char *valmime, char *valctc, char *valdir, char* valperm)
{
    DIR *dirp;         // pointeur de répertoire
    struct dirent *dp; // pointeur de fichier

    if (!(dirp = opendir(name))) // ouvre le repertoire
        return;

    while ((dp = readdir(dirp)) != NULL) // tant qu'il y a des fichiers
    {

        int test_valide = 1;
        int test_ouvalide=0;
        if (dp->d_type == DT_DIR) // si c'est un répertoire (DT_DIR est le type répertoire)
        {
            char path[1024];                                                   // création d'un chemin
            if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) // si c'est le répertoire courant ou le répertoire parent
                continue;

            snprintf(path, sizeof(path), "%s/%s", name, dp->d_name); // on concatène le chemin du répertoire courant avec le nom du répertoire

            if (FLAG_DIR == 1)
            {
                if (FLAG_DIROPTION == 1)
                {
                    //récupere dans un chemin en char* le dernier dossier
                    char *temp[1024]; // on initialise temp   
                    snprintf(temp, sizeof(temp), "%s/%s", name, dp->d_name);
                    char *dossier = strrchr(temp, '/');
                    dossier = dossier + 1;
                    if (compar_name(valdir, dossier) == true)
                    {
                        if (FLAG_COLOR==1){
                            printf("\033[00;32m%s\n", path);
                            continue;
                        }
                        else{
                            printf("%s\n", path);
                            continue;
                        }
                        
                    }
                }
                else
                {
                    if (FLAG_COLOR==1){
                        printf("\033[00;32m%s\n", path);
                        continue;
                    }
                    else{
                        printf("%s\n", path);
                        continue;
                    }
                    
                }
                
            }
            if (FLAG_NOOPTION == 1)
            {
                printf("%s/%s\n", name, dp->d_name);
            }
            
            // on affiche le nom du répertoire
            listdir(path, valsize, valname, valdate, valmime, valctc, valdir, valperm); // on appelle la fonction récursivement
        }
        else // si c'est un fichier
        {
            if (FLAG_DIR == 0)
            {
                char *temp[1024]; //initialisation
                snprintf(temp, sizeof(temp), "%s/%s", name, dp->d_name);

                if (FLAG_SIZE == 1)
                {

                    if (compar_size(valsize, temp) == false)
                    {
                        test_valide = 0;
                    }
                    else{
                        test_ouvalide=1;
                    }
                }
                if (FLAG_NAME == 1)
                {

                    if (compar_name(valname, dp->d_name) == false)
                    {
                        test_valide = 0;
                    }
                    else{
                        test_ouvalide=1;
                    }
                }
                if (FLAG_DATE == 1)
                {

                    if (dernier_acces(valdate, temp) == false)
                    {
                        test_valide = 0;
                    }
                }
                if (FLAG_MIME == 1)
                {

                    char *last = valmime + strlen(valmime) - 1;

                    if (!FLAG_MIMESLASH)
                    {
                        if (*last != '*')
                        {
                            strcat(valmime, "/*");
                        }
                    }
                    else
                    {
                        if (*last == '/')
                        {
                            strcat(valmime, "*");
                        }
                    }

                    if (valmime != NULL)
                    {
                        if (compar_mime(valmime, temp) == false)
                        {

                            test_valide = 0;
                        }
                    }
                    else{
                        test_ouvalide=1;
                    }
                }

                if (FLAG_PERM == 1)
                {

                    if (compar_perm(valperm, temp) == false)
                    {
                        test_valide = 0;
                    }
                    else{
                        test_ouvalide=1;
                    }
                }

                if (FLAG_CTC == 1)
                {

                    if (lecture(valctc, temp) == false)
                    {
                        test_valide = 0;
                    }
                    else{
                        test_ouvalide=1;
                    }
                }

                if (FLAG_OU == 1){
                    if (test_ouvalide==1 && FLAG_COLOR == 0){
                        printf("%s/%s\n", name, dp->d_name); // on affiche le nom du fichier
                    }
                    else if (test_ouvalide==1 && FLAG_COLOR == 1){
                        printf("\033[00;32m%s/\033[00;31m%s\033[00m\n", name, dp->d_name); // on affiche le nom du fichier
                    }
                }


                else{
                    if (test_valide == 1 && FLAG_COLOR == 0)
                    {
                        printf("%s/%s\n", name, dp->d_name); // on affiche le nom du fichier
                    }
                    else if (test_valide == 1 && FLAG_COLOR == 1)
                    {
                        printf("\033[00;32m%s/\033[00;31m%s\033[00m\n", name, dp->d_name); // on affiche le nom du fichier
                    }
                } 
            }
        }
    }
    closedir(dirp); // on ferme le répertoire
}

// main parse les arguments et lance la fonction listdir
int main(int argc, char *argv[])
{

    int size = strlen(*argv);
    char *valsize = "ini";
    char *valname = "ini";
    char *valdate = "ini";
    char *valmime = "ini";
    char *valctc = "ini";
    char *valdir = "ini";
    char *valperm = "ini";
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
                if (argv[i + 1] == NULL || strcmp(argv[i + 1], "-test") == 0 || strcmp(argv[i + 1], "-name") == 0 || strcmp(argv[i + 1], "-size") == 0 || strcmp(argv[i + 1], "-date") == 0 || strcmp(argv[i + 1], "-mime") == 0 || strcmp(argv[i + 1], "-ctc") == 0 || strcmp(argv[i + 1], "-dir") == 0 || strcmp(argv[i + 1], "-color") == 0 || strcmp(argv[i + 1], "-ou") == 0){
                    fprintf(stderr, "Pas de paramètre indiqué après -size.\n");
                    exit(0);
                }

                valsize = argv[i + 1];
            };
            if (strcmp(argv[i], "-name") == 0)
            {
                FLAG_NAME = 1;
                if (argv[i + 1] == NULL || strcmp(argv[i + 1], "-test") == 0 || strcmp(argv[i + 1], "-name") == 0 || strcmp(argv[i + 1], "-size") == 0 || strcmp(argv[i + 1], "-date") == 0 || strcmp(argv[i + 1], "-mime") == 0 || strcmp(argv[i + 1], "-ctc") == 0 || strcmp(argv[i + 1], "-dir") == 0 || strcmp(argv[i + 1], "-color") == 0 || strcmp(argv[i + 1], "-ou") == 0){
                    fprintf(stderr, "Pas de paramètre indiqué après -name.\n");
                    exit(0);
                }
                valname = argv[i + 1];
            }

            if (strcmp(argv[i], "-date") == 0)
            {
                FLAG_DATE = 1;
                if (argv[i + 1] == NULL || strcmp(argv[i + 1], "-test") == 0 || strcmp(argv[i + 1], "-name") == 0 || strcmp(argv[i + 1], "-size") == 0 || strcmp(argv[i + 1], "-date") == 0 || strcmp(argv[i + 1], "-mime") == 0 || strcmp(argv[i + 1], "-ctc") == 0 || strcmp(argv[i + 1], "-dir") == 0 || strcmp(argv[i + 1], "-color") == 0 || strcmp(argv[i + 1], "-ou") == 0){
                    fprintf(stderr, "Pas de paramètre indiqué après -date.\n");
                    exit(0);
                }
                valdate = argv[i + 1];
            }
            if (strcmp(argv[i], "-mime") == 0)
            {

                FLAG_MIME = 1;
                if (argv[i + 1] == NULL || strcmp(argv[i + 1], "-test") == 0 || strcmp(argv[i + 1], "-name") == 0 || strcmp(argv[i + 1], "-size") == 0 || strcmp(argv[i + 1], "-date") == 0 || strcmp(argv[i + 1], "-mime") == 0 || strcmp(argv[i + 1], "-ctc") == 0 || strcmp(argv[i + 1], "-dir") == 0 || strcmp(argv[i + 1], "-color") == 0 || strcmp(argv[i + 1], "-ou") == 0){
                    fprintf(stderr, "Pas de paramètre indiqué après -mime.\n");
                    exit(0);
                }
                valmime = argv[i + 1];

                for (int i = 0; i < strlen(valmime); i++)
                {
                    if (valmime[i] == '/')
                    {
                        FLAG_MIMESLASH = true;
                    }
                }
            }

            if (strcmp(argv[i], "-ctc") == 0)
            {
                FLAG_CTC = 1;
                if (argv[i + 1] == NULL || strcmp(argv[i + 1], "-test") == 0 || strcmp(argv[i + 1], "-name") == 0 || strcmp(argv[i + 1], "-size") == 0 || strcmp(argv[i + 1], "-date") == 0 || strcmp(argv[i + 1], "-mime") == 0 || strcmp(argv[i + 1], "-ctc") == 0 || strcmp(argv[i + 1], "-dir") == 0 || strcmp(argv[i + 1], "-color") == 0 || strcmp(argv[i + 1], "-ou") == 0){
                    fprintf(stderr, "Pas de paramètre indiqué après -ctc.\n");
                    exit(0);
                }
                valctc = argv[i + 1];
            }

            if (strcmp(argv[i], "-dir") == 0)
            {
                FLAG_DIR = 1;
                if (argv[i + 1] == NULL || strcmp(argv[i + 1], "-test") == 0 || strcmp(argv[i + 1], "-name") == 0 || strcmp(argv[i + 1], "-size") == 0 || strcmp(argv[i + 1], "-date") == 0 || strcmp(argv[i + 1], "-mime") == 0 || strcmp(argv[i + 1], "-ctc") == 0 || strcmp(argv[i + 1], "-dir") == 0 || strcmp(argv[i + 1], "-color") == 0 || strcmp(argv[i + 1], "-ou") == 0){
                    fprintf(stderr, "Pas de parametre indique apres -dir\n");
                    exit(0);
                }
                valdir = argv[i + 1];
                //get the first letter of a char*
                if (valdir!=NULL){
                    char first = valdir[0];
                    if (first!='-'){
                        FLAG_DIROPTION=1;
                    }
                }
                
            }
            if (strcmp(argv[i],"-ou")==0){
                FLAG_OU=1;
            }
            if (strcmp(argv[i], "-color") == 0)
            {
                FLAG_COLOR = 1;
            }
            if (strcmp(argv[i], "-perm") ==0)
            {
                FLAG_PERM = 1;
                valperm = argv[i+1];
            }

            i++;
        }
    }

    if (FLAG_TEST == 0)
    {
        if (argv[1] == NULL){
            fprintf(stderr,"Pas de point de départ indiqué\n");
            exit(0);
        }
        STARTING_POINT = argv[1];
        
        if (STARTING_POINT[strlen(STARTING_POINT) - 1] == '/')
        {
            STARTING_POINT[strlen(STARTING_POINT) - 1] = '\0';
        }
        listdir(STARTING_POINT, valsize, valname, valdate, valmime, valctc, valdir,valperm);
    }
    
    return 0;
}
