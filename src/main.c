// #include "trie.h"
#include "dawg.h"

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
    Dawg tree2 = construct("../dict/german-wordlist.txt");
    Dawg tree = construct("../dict/test.txt");
    if (dawg_search(tree, "zygomas"))
        printf("yes\n");
    else printf("NO\n");
    return 0;
}
