#ifndef __TRIE_H
#define __TRIE_H

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"

typedef struct trie {
    struct trie * fils[26];
    bool est_mot;
} *Trie;

Trie trie_init();
Trie trie_insert(Trie t, char * mot);
bool trie_rech(Trie t, char * mot);
void trie_sup(Trie t);

#endif