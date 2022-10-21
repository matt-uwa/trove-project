/**
 * This is to compress / unzip
 * trovefile and save to disk
 * write trove file data to gzip using pipes
 */

#include "trove.h"

/**
 * THIS FUNCTION SHOULD RECREATE THE HASHTABLE STRUCTURE
 * BY UNZIPPING THE TROVEFILE AND BREAKING APART EACH
 * LINE OF THE FILE 
 */
void unzipTrovefile(void) {
    int thepipe[2];
    if (pipe(thepipe) != 0) {
        perror("Error creating pipe!\n");
        exit(EXIT_FAILURE);
    }
    switch(fork()) {
        case -1 :
            printf("fork() failed\n");
            exit(EXIT_FAILURE);
        case 0 :
            close(thepipe[1]);
            dup2(thepipe[0], 0);
            char lineBuf;
            char *line = (char*) malloc(1);
            while (read(0, &lineBuf, sizeof(char)) > 0) {
                if (lineBuf != '\n') {
                    line = (char*) realloc(line, strlen(line) * sizeof(char) + 1);
                    strncat(line, &lineBuf, 1);
                } else {
                    printf("    %s", line);
                    char index[4];
                    bool indexFound = false;
                    LIST *pathNames = list_new();
                    char *path = malloc(1);
                    for (int i = 0; i < strlen(line); i++) {
                        if (line[i] != ',') {
                            if (!indexFound) {
                                strncat(index, &line[i], 1);
                            } else {
                                path = realloc(path, strlen(path) * sizeof(char) + 1);
                                strncat(path, &line[i], 1);
                            }
                        } else {
                            if (!indexFound) {
                                indexFound = true;                            

                            } else {
                                list_add(pathNames, path);
                            }
                        }
                        hashtable[atoi(index)] = pathNames;
                    }
                    free(line);
                }
            } 

            close(thepipe[0]);
            break;
        default :
            close(thepipe[0]);
            char compressedTrovePath[strlen(trovePath) * sizeof(char) + 3];
            strcpy(compressedTrovePath, trovePath);
            strcat(compressedTrovePath, ".gz");
            printf("%s\n", compressedTrovePath);
            int fd = open(compressedTrovePath, O_RDONLY);
            execl("/usr/bin", "zcat", fd, (char*) NULL);
            char buf;
            while (read(fd, &buf, 1) > 0) {
                printf("    ... TEST ...\n");
                write(thepipe[1], &buf, 1);
            }
            close(thepipe[1]);
            break;
    }
}

/**
 * WRITES DATA TO THE TROVEFILE
 * FORMAT: HASH_INDEX, PATHNAME1, PATHNAME2, ...
 * COMPRESSES TROVEFILE USING GZIP UTILITY 
 */
void trovefile(void){
    int thepipe[2];

    if(pipe (thepipe) != 0){
        perror("Error creating pipe!\n");
        exit(EXIT_FAILURE);
    }

    switch(fork()){
        case -1 :
            printf("fork() failed\n");
            exit(EXIT_FAILURE);
        // THIS IS THE CHILD PROGRESS THAT WRITES TO THE FILE AND COMPRESSES
        case 0 :
            // reads from parent process
            // writes to stdout
            close(thepipe[1]);
            dup2(thepipe[0], 0);
            char buf;
            int fd1 = open(trovePath, O_RDWR | O_CREAT);
            while(read(0, &buf, thepipe[1]) > 0){
                    write(fd1, &buf, thepipe[1]);
            }
            close(thepipe[0]);
            printf("    .... COMPRESSING %s ....\n", trovePath);
            execl("/usr/bin", "gzip", fd1, (char*) NULL);
            break;
        // THIS IS THE PARENT PROCESS THAT'LL READ THE HASHTABLE
        default:
            // writes to the pipe for the child to read
            close(thepipe[0]);
            char *line;
            for(int i = 0 ; i < ARRAYSIZE ; i++){
                if(hashtable[i] != NULL){
                    char txt[sizeof(i)];
                    sprintf(txt, "%d", i);
                    line = (char*) malloc(strlen(txt) * sizeof(char));
                    strcpy(line, txt);
                    while(hashtable[i] != NULL){
                        char *path = hashtable[i]->word;
                        line = (char*) realloc(line, strlen(line) + strlen(path) + 3);
                        strcat(line, ", ");
                        strcat(line, path);
                        hashtable[i] = hashtable[i]->nextWord;
                    }
                    line = (char*) realloc(line, strlen(line) * sizeof(char) + 2);
                    strcat(line, "\n");
                    printf("    --------- WRITING LINE TO TROVEFILE:\n");
                    printf("    %s", line);
                    write(thepipe[1], line, strlen(line) * sizeof(char));
                    free(line);
                }
            }
            close(thepipe[1]);
            break;
    }
}