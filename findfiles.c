#include "trove.h"
// Find each individual file that should be indexed
// Add absolute pathname to array?

// dirName should be the absolute pathname of the root file
void findfiles(char* dirName) {
    FILE* fp = fopen(dirName, "r");
    DIR* dir = opendir(dirName);
    if (fp != NULL && dir == NULL) {
        printf("file found: %s\n", dirName);
        fclose(fp);
        return;
    }
    fclose(fp);
    
    if (dir == NULL) {
        printf("%s: directory not found\n", dirName);
        exit(EXIT_FAILURE);
    }


    struct dirent* entity;

    entity = readdir(dir);
    while (entity != NULL) {
        
        if (entity->d_type == 4) {
            if (strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0) {
                char newPath[100] = { 0 };
                strcat(newPath, dirName);
                strcat(newPath, "/");
                strcat(newPath, entity->d_name);
                printf("directory found: %s\n", newPath);
                findfiles(newPath);
            }
        } else {
            // entity is not a directory so add to files to be read.
            // call indexing() here??
            printf("file found : %s\n", entity->d_name);
        }
        entity = readdir(dir);
    }
    
    closedir(dir);
}