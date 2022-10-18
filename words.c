#include "trove.h"
#include <ctype.h>
#include <stdbool.h>

// DEBUGGING: Prints uniqueWords array.
void printUnique(char **wordArr, int numWords) {
    int i;
    for (i=0; i<numWords; i++) {
        printf("%s\n", wordArr[i]);
    }
    printf("---------------\n");
}

// Iterates through the given array and verifies the given word
// is not contained within the array.
bool notInArray(char *word, char *wordsArr[], int numWords) {
    int i;
    for (i = 0; i < numWords; i++) {
        if (strlen(wordsArr[i]) == strlen(word)) {
            if (strcmp(wordsArr[i], word) == 0) {
                return false;
            }
        }
    }
    return true;
}

void words(char *fileContents) {
    int i = 0;
    char character = fileContents[i];
    char *currentWord;
    // worst case is that the entire file is words that all unique and are all minLength chars long.
    // For this case the number of unique words = number of chars / (minLength-1)
    // -1 accounts for the non alphanumeric char.
    char *uniqueWords[strlen(fileContents) / (minLength - 1)];
    int numUniqueWords = 0;


    // initialises currentWord to be a single character string
    currentWord = (char *) malloc(sizeof(char));
    while (character != '\0') {
        if (isalnum(character)) {
            // increases the size of the currentWord string by one character
            currentWord = (char *) realloc(currentWord, sizeof(currentWord) + sizeof(char));
            // appends character to currentWord string
            strncat(currentWord, &character, 1);
        } else {
            if (strlen(currentWord) >= minLength && notInArray(currentWord, uniqueWords, numUniqueWords)) {
                int wordLength = strlen(currentWord);
                // Allocate memory in uniqueWords array for the current word.
                uniqueWords[numUniqueWords] = (char *) malloc(sizeof(char) * (wordLength + 1));
                // Copies currentWord into uniqueWords array.
                strcpy(uniqueWords[numUniqueWords], currentWord);
                numUniqueWords++;
            }
            // resets the currentWord string
            memset(currentWord, 0, strlen(currentWord));
        }
        // Moves to the next character in fileContents
        i++;
        character = fileContents[i];
    }
    printUnique(uniqueWords, numUniqueWords);
}