#include "trie.h"

/**
 *  initialize Trie
*/
Trie trie_init()
{
    Trie nt = (Trie) malloc (sizeof(struct trie));
    if (nt == NULL)
        exit(EXIT_FAILURE);
    for (int i = 0; i < 26; i++)
        nt->childrens[i] = NULL;
    nt->is_word = false;
    return nt;
}

/**
 *  insert 'word' in the trie, if the word sequence already exist, update is_word to true.
 *  else, if the prefix of the word exist, add the missing part and mark the last char 'is_word' as true.
*/
Trie trie_insert(Trie t, char * word)
{
    int lgr;
    int ind;

    Trie tmp = t;
    parse_word(word);
    lgr = strlen(word);
    if (!lgr)
    {
        perror("invalid input\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < lgr; i++)
    {
        ind = ascii_to_index(word[i]);
        if (tmp->childrens[ind] == NULL)
            tmp->childrens[ind] = trie_init();
        tmp = tmp->childrens[ind];
    }
    tmp->is_word = true;
    return t;
}

/**
 *  Searching the 'word' in the Trie, 
 *  take O(n) to find it, where n is the length of 'word'
*/
bool trie_search(Trie t, char *word)
{
    int lgr;
    int ind;

    Trie tmp = t;
    parse_word(word);
    lgr = strlen(word);
    if (!lgr)
    {
        perror("invalid input\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < lgr; i++)
    {
        ind = ascii_to_index(word[i]);
        if (tmp->childrens[ind] == NULL)
            return false;
        tmp = tmp->childrens[ind];
    }
    return (tmp != NULL && tmp->is_word);
}


/**
 *  Delete Trie 
*/
void trie_delete(Trie t)
{
    for (int i = 0; i < 26; i++)
    {
        if (t->childrens[i] != NULL)
            trie_delete(t->childrens[i]);
    }
    free(t);
    t = NULL;
}
