#ifndef __DAWG_H
#define __DAWG_H
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"
#include "hashmap.h"
#include "stack.h"

typedef struct          s_dawg_node
{
    int          label;
    struct s_dawg_node  *children[26];
    bool                isWord;
    
    // char c;
}                       *Dawg_node;

typedef struct  s_edge
{
    char        letter;
    Dawg_node   left;
    Dawg_node   right;
}               *Edge;

typedef struct          s_dawg
{
    char                *last_word;
    Dawg_node           root;
    struct hashmap_s    *registered;
    Stack               unregistered;
    int                 id;
    int         size;
}                       *Dawg;

void    dawg_insert(Dawg tree, char*   word);
void    dawg_finish(Dawg tree);
Dawg    dawg_init();
bool    dawg_search(Dawg tree, char *word);
void    dawg_print(Dawg_node root, int space);

#endif