#include "construct.h"


/**
 * Construct DAWG Tree from dictionary file passed as args
*/
Dawg construct_dawg(char *dict)
{
    // Instantiate either a Trie or a DAWG here
    Dawg tree = dawg_init();

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE *fp;

    // open file
    fp = fopen(dict, "r"); // read mode
    if (fp == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    // read file
    while ((read = getline(&line, &len, fp)) != -1) {
        // remove newline
        size_t length = strlen(line);
        if((length > 0) && (line[length-1] == '\n'))
        {
            line[length-1] ='\0';
        }
        dawg_insert(tree, line);
    }
    dawg_finish(tree);
    fclose(fp);
    free(line);
    return tree;
}

/**
 * Construct Trie from dictionary file passed as args
*/
Trie construct_trie(char *dict)
{
    // Instantiate either a Trie or a DAWG here
    Trie tree = trie_init();

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE *fp;

    // open file
    fp = fopen(dict, "r"); // read mode
    if (fp == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    // read file
    while ((read = getline(&line, &len, fp)) != -1) {
        // remove newline
        size_t length = strlen(line);
        if((length > 0) && (line[length-1] == '\n'))
        {
            line[length-1] ='\0';
        }
        trie_insert(tree, line);
    }
    fclose(fp);
    free(line);
    return tree;
}