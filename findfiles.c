#include "trove.h"

void findfiles(char *dirName) {
    struct dirent* entity;
    DIR* dir = opendir(dirName);

    // Check that the directory could be opened
    if (dir == NULL) {
        printf("%s: error opening directory.\n", dirName);
        exit(EXIT_FAILURE);
    }
    entity = readdir(dir);
    while (entity != NULL) {
        // check for the type of entity (DT_DIR is a directory) (DT_REG is a regular file)
        // not interested in "." and ".." directories as they will create meaningless loop
        if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0) {
            // updating the relative pathName to include the new directory
            char newPath[100] = { 0 };
            strcat(newPath, dirName);
            strcat(newPath, "/");
            strcat(newPath, entity->d_name);
            printf("DIRECTORY FOUND : %s\n", newPath);
            // recursive call to findfiles to investigate new directory
            findfiles(newPath);
        } else if (entity->d_type == DT_REG) {
            // the entity is a regular file => file should be indexed
            char newPath[100] = { 0 };
            strcat(newPath, dirName);
            strcat(newPath, "/");
            strcat(newPath, entity->d_name);
            printf("FILE FOUND : %s\n", newPath);
            indexing(newPath);
        }
        entity = readdir(dir);
    }
    closedir(dir);
}