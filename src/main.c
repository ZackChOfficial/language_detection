// #include "trie.h"
#include "dawg.h"

/*
 * Copy this function template to construct either a DAWG or a trie
 * based on the dictionary filename given
 *
 * Don't forget to change the void return type of this function
 */
Dawg construct(char *dict) {
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
    printf("hi\n");
    while ((read = getline(&line, &len, fp)) != -1) {
        // remove newline
        size_t length = strlen(line);
        if((length > 0) && (line[length-1] == '\n'))
        {
            line[length-1] ='\0';
        }

        // here insert the word in the trie or in the DAWG
        printf("ko\n");
        dawg_insert(tree, line);
        printf("ok\n");
    }
    printf("hi\n");
    dawg_finish(tree);
    fclose(fp);
    free(line);
    return tree;
}

int main(int argc, char* argv[]) {
    // construct("dict/french-wordlist.txt");
    Dawg tree = construct("../dict/english-wordlist.txt");
    if (dawg_search(tree, "zulus"))
        printf("yes\n");
    else printf("NO");
    // construct("dict/german-wordlist.txt");
    // Here listen for user input, parse it and detect the language of the given text
    // To complete ...
    return 0;
}
