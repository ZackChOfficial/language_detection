#ifndef __CONSTRUCT_H
#define __CONSTRUCT_H

#include "dawg.h"
#include "trie.h"


Dawg    construct_dawg(char *dict);
Trie    construct_trie(char *dict);

#endif