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
    int i=0;
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

int main(int argc, char* argv[]) {
    Dawg tree1 = construct("../dict/french-wordlist.txt");
    // Dawg tree2 = construct("../dict/german-wordlist.txt");
    Dawg tree = construct("../dict/english-wordlist.txt");
    // dawg_print(tree->root, 0);
    if (dawg_search(tree, "zygomasc"))
        printf("yes\n");
    else printf("NO\n");
    // printf("nb nodes: %d\n", tree->size);
    // construct("dict/german-wordlist.txt");
    // Here listen for user input, parse it and detect the language of the given text
    // To complete ...
    return 0;
}
