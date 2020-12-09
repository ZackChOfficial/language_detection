#include <stdio.h>
#include <string.h>

#include "utils.h"

/**
 * Change ASCII char (a-z) to array index
 * a -> 0, b -> 1, c -> 2, ..., z -> 25
 */
size_t ascii_to_index(char c) {
    size_t index = (size_t) c;

    if(index < 97 || index > 122) {
        perror("ascii_to_index function can only read lowercase letter a-z.\n");
        exit(EXIT_FAILURE);
    }

    return index - 97;
}

/**
 * Remove char from string at the given index
 */
void remove_char(char *word, size_t index) {
    memmove(&word[index],&word[index+1],strlen(word)-index);
}

/**
 * Remove all char from given string that aren't a-z 
 */
void parse_word(char *word) {
    for(size_t i = 0; i < strlen(word); i++) {
        size_t index = (size_t) word[i];
        if(index < 97 || index > 122) {
            remove_char(word, i);
        }
    }
}

/**
 * Concat two strings together
 */
char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}