#include "trie.h"

// Initialise un trie et le renvoie.
Trie trie_init()
{
    Trie nt = (Trie) malloc (sizeof(struct trie));
    if (nt == NULL)
        exit(EXIT_FAILURE);
    for (int i = 0; i < 26; i++)
        nt->fils[i] = NULL;
    nt->est_mot = false;
    return nt;
}


// Insère le mot 'mot' dans le trie 't'. Si mot est déjà dans le t, il met à jour le
// champ est_mot. Si le début de mot est déjà dans t, il part de ce préfixe pour le
// nouveau mot.
Trie trie_insert(Trie t, char * mot)
{
    int lgr;
    int ind;

    Trie tmp = t;
    parse_word(mot);
    lgr = strlen(mot);
    if (!lgr)
    {
        perror("invalid input\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < lgr; i++)
    {
        ind = ascii_to_index(mot[i]);
        if (tmp->fils[ind] == NULL)
            tmp->fils[ind] = trie_init();
        tmp = tmp->fils[ind];
    }
    tmp->est_mot = true;
    return t;
}

// Recherche le mot 'mot' dans le trie 't'. Renvoie true d'il y est, false sinon
bool trie_rech(Trie t, char * mot)
{
    int lgr;
    int ind;

    Trie tmp = t;
    parse_word(mot);
    lgr = strlen(mot);
    if (!lgr)
    {
        perror("invalid input\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < lgr; i++)
    {
        ind = ascii_to_index(mot[i]);
        if (tmp->fils[ind] == NULL)
            return false;
        tmp = tmp->fils[ind];
    }
    return (tmp != NULL && tmp->est_mot);
}

void trie_sup(Trie t)
{
    for (int i = 0; i < 26; i++)
    {
        if (t->fils[i] != NULL)
            trie_sup(t->fils[i]);
    }
    free(t);
    t = NULL;
}
