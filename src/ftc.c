#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

void listdir(const char *name, int indent)
{
    DIR *dirp;
    struct dirent *dp;

    if (!(dirp = opendir(name)))
        return;

    while ((dp = readdir(dirp)) != NULL)
    {
        if (dp->d_type == DT_DIR)
        {
            char path[1024];
            if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, dp->d_name);
            printf("%*s[%s]\n", indent, "", dp->d_name);
            listdir(path, indent + 2);
        }
        else
        {
            printf("%*s- %s\n", indent, "", dp->d_name);
        }
    }
    closedir(dirp);
}
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