#include "construct.h"
#define length 4096
#define FRENCH_DICT "./dict/french-wordlist.txt"
#define ENGLISH_DICT "./dict/english-wordlist.txt"
#define GERMAN_DICT "./dict/german-wordlist.txt"

int     choose_algo()
{
    int     algo;
    char    input[100];

    printf("1 - DAWG\n");
    printf("2 - Trie\n");
    while (1)
    {
        printf("Please choose one of the above algorithm: ");
        scanf("%s", input);
        algo = atoi(input);
        if (algo != 1 && algo != 2)
            printf("Invalid choice.\n");
        else return algo;
    }
}

char       *get_input()
{
    char    *string;
    char    c;
    size_t     len = length;

    string = (char*)malloc(sizeof(char) * length);
    scanf("%c", &c);
    if (!string)
        exit(EXIT_FAILURE);
    getline(&string, &len, stdin);
    return string;
}

void        print_language(int fr, int en, int ger)
{
    if (en > fr && en > ger)
        printf("Language: English\n");
    else if (fr > en && fr > ger)
        printf("Language: French\n");
    else if (ger > en && ger > fr)
        printf("Language: German\n");
    else
    printf("Language: uncertain\n"); 
}

void        detect_with_dawg(char  *string)
{
    Dawg    french = construct_dawg(FRENCH_DICT);
    Dawg    german = construct_dawg(GERMAN_DICT);
    Dawg    english = construct_dawg(ENGLISH_DICT);
    int     fr = 0;
    int     en = 0;
    int     ger = 0;
    char    *word;

    word = strtok(string, " ");
    while (word != NULL)
    {
        if (dawg_search(french, word))
            fr++;
        if (dawg_search(english, word))
            en++;
        if (dawg_search(german, word))
            ger++;
        word = strtok(NULL, " ");
    }
    print_language(fr,en,ger);
}

void detect_with_trie(char  *string)
{
    Trie    french = construct_trie(FRENCH_DICT);
    Trie    german = construct_trie(GERMAN_DICT);
    Trie    english = construct_trie(ENGLISH_DICT);
    int     fr = 0;
    int     en = 0;
    int     ger = 0;
    char    *word;

    word = strtok(string, " ");
    while (word != NULL)
    {
        if (trie_rech(french, word))
            fr++;
        if (trie_rech(english, word))
            en++;
        if (trie_rech(german, word))
            ger++;
        word = strtok(NULL, " ");
    }
    print_language(fr,en,ger);
}

int main() {

    int     algo;
    char    *string;

    algo = choose_algo();
    string = get_input();
    if (algo == 1)
        detect_with_dawg(string);
    else
        detect_with_trie(string);
    free(string);
    return 0;
}
