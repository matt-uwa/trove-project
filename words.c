#include "trove.h"
#include "ctype.h"

void words(char *fileContents) {
    int i = 0;
    char character = fileContents[i];
    char *currentWord;

    // initialises currentWord to be a single character string
    currentWord = (char *) malloc(sizeof(char));
    while (character != '\0') {
        if (isalnum(character)) {
            // increases the size of the currentWord string by one character
            currentWord = (char *) realloc(currentWord, sizeof(currentWord) + sizeof(char));
            // appends character to currentWord string
            strncat(currentWord, &character, 1);
        } else {
            printf("%ld : %s\n", strlen(currentWord), currentWord);

            // resets the currentWord string
            memset(currentWord, 0, strlen(currentWord));
        }
        // Moves to the next character in fileContents
        i++;
        character = fileContents[i];
    }
}