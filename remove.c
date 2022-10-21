#include "trove.h"

// remove any information from given file.

void removeData(char *pathName) {
    unzipTrovefile();
    
    // iterate through trovefile
    int i;
    for (i = 0; i < ARRAYSIZE; i++) {
        LIST *currWord = hashtable[i];
        // Loops every list element comparing file names
        while (currWord->nextWord != NULL) {
            if (strlen(currWord->word) == strlen(pathName)) {
                if (strcmp(currWord->word, pathName)) {
                    currWord->word = NULL;
                }
            }
        }
    }
}