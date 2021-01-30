#ifndef __TRIE_H
#define __TRIE_H

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"

typedef struct trie {
    struct trie *childrens[26];
    bool is_word;
} *Trie;

Trie trie_init();
Trie trie_insert(Trie t, char *word);
bool trie_search(Trie t, char *word);
void trie_delete(Trie t);

#endif