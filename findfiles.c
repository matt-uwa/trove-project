#include "trove.h"

void findfiles(char *dirName) {
    struct dirent* entity;
    DIR* dir = opendir(dirName);
    if (dir == NULL) {
        printf("%s: error opening directory.\n", dirName);
        exit(EXIT_FAILURE);
    }
    entity = readdir(dir);
    while (entity != NULL) {
        if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0) {
            char newPath[100] = { 0 };
            strcat(newPath, dirName);
            strcat(newPath, "/");
            strcat(newPath, entity->d_name);
            printf("DIRECTORY FOUND : %s\n", newPath);
            findfiles(newPath);
        } else if (entity->d_type == DT_REG) {
            char newPath[100] = { 0 };
            strcat(newPath, dirName);
            strcat(newPath, "/");
            strcat(newPath, entity->d_name);
            printf("FILE FOUND : %s\n", newPath);
        }
        entity = readdir(dir);
    }
    closedir(dir);
}