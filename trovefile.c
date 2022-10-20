#include "trove.h"

// Compress / unzip trovefile and save to disk (write trove file data to gzip using pipes)

void trovefile(void) {
    int thepipe[2];

    if (pipe(thepipe) != 0) {
        perror("Error creating pipe!\n");
        exit(EXIT_FAILURE);
    }

    switch (fork()) {
        case -1 :
            printf("fork() failed!\n");
            exit(EXIT_FAILURE);
        
        case 0 :
        // reads from the parent process
        // writes to stdout (terminal)
            close(thepipe[1]);
            dup2(thepipe[0], 0);
            char buf;
            int fd1 = open(trovePath, O_WRONLY | O_CREAT);
            while (read(0, &buf , thepipe[1]) > 0) {
                write(fd1, &buf , thepipe[1]);
            }
            close(thepipe[0]);

            execl("/usr/bin", "gzip", fd1, (char*) NULL);

            // perror("/usr/bin/gzip\n");
            
            break;
        
        default :
        // writes to the pipe for child to read
            close(thepipe[0]);
            // dup2(thepipe[1], 1);
            for (int i = 0; i < ARRAYSIZE; i++) {
                char *troveLine;
                printf("... %s ...\n", hashtable[i]->word);
                if (hashtable[i]->word != NULL) {
                    char index[sizeof(i) + 1];
                    sprintf(index, "%d", i);
                    troveLine = malloc(sizeof(index));
                    strcat(troveLine, index);
                    char *path = hashtable[i]->word;
                    while (path != NULL) {
                        troveLine = realloc(troveLine, sizeof(troveLine) + sizeof(path) + 3);
                        strcat(troveLine, ", \0");
                        strcat(troveLine, path);
                        path = hashtable[i]->nextWord->word;
                    }
                    troveLine = realloc(troveLine, sizeof(troveLine) + 1);
                    strcat(troveLine, "\n");
                    write(thepipe[1], troveLine, sizeof(troveLine));
                }
            }
            close(thepipe[1]);

            break;
    }
}