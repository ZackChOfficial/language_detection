#include "dawg.h"

/**
 * return length of common part of two strings 
*/
int Common_prefix(char   *word1, char    *word2)
{
    int size;

    size = MIN(strlen(word1), strlen(word2));
    for (int i=0; i < size; i++)
    {
        if (word2[i] != word1[i])
            return i;
    }
    return size;
}

/**
 * Return new DAWG Node
*/
Dawg_node create_new_Dawg_node(int id)
{
    Dawg_node newNode;

    newNode = (Dawg_node)malloc(sizeof(struct s_dawg_node));
    if (!newNode)
        exit(EXIT_FAILURE);
    newNode->label = id;
    for (int i = 0; i < 26; i++)
        newNode->children[i] = NULL;
    newNode->isWord = false;
    return newNode;
}
/**
 * Return New DAWG Edge
*/
Edge create_new_edge(Dawg_node left, Dawg_node right, char label)
{
    Edge newEdge = (Edge)malloc(sizeof(struct s_edge));
    if (!newEdge)
        exit(EXIT_FAILURE);
    newEdge->left = left;
    newEdge->right = right;
    newEdge->letter = label;
    return newEdge;
}

/**
 *  Return key of a node to use it in the Hashmap 
*/
char    *get_key(Dawg_node node)
{
    char    *key;
    char    *l;

    key = "";
    if (node->isWord)
        key = concat(key, "1");
    else 
        key = concat(key, "0");
    key = concat(key, "_");
    for (int i=0; i < 26; i++)
    {
        if (node->children[i])
        {
            l= (char *)malloc(sizeof(char)*2);
            l[0] = i + 'a';
            l[1] = '\0';
            key = concat(key, l);
            key = concat(key, "_");
            key = concat(key, ft_itoa(node->children[i]->label));
            key = concat(key, "_");
        }
    }
    return key;
}

/**
 * Minimizing the tree by removing the shared suffixe parts
*/
void dawg_minimize(Dawg tree, int depth)
{
    Edge        edge;
    Dawg_node   parent;
    Dawg_node   child;
    Dawg_node   newChild;
    char        label;
    char        *key;

    while (stack_size(tree->unregistered) > depth)
    {
        edge = stack_pop(tree->unregistered);
        parent = edge->left;
        child = edge->right;
        label = edge->letter;
        key = get_key(child);
        newChild = hashmap_get(tree->registered, key, strlen(key));
        if (newChild != NULL)
        {
            parent->children[ascii_to_index(label)] = newChild;
            free(child);
            tree->size--; // keep tracking the number of nodes
        }
        else
            hashmap_put(tree->registered,key, strlen(key), child);
    }
}

/**
 * Insert new word in the tree
*/
void dawg_insert(Dawg tree, char    *word)
{
    Edge        edge;
    Edge        newEdge;
    Dawg_node   node;
    Dawg_node   newNode;
    int         length;
    int         common_prefix;

    parse_word(word);
    length = strlen(word);
    if (strcmp(tree->last_word, word) > 0)
    {
        perror("Words must be in alphabetical order\n");
        exit(EXIT_FAILURE);
    }
    if (!length)
        return;
    common_prefix = Common_prefix(tree->last_word, word);
    dawg_minimize(tree,common_prefix);
    if (!is_stack_empty(tree->unregistered))
    {
        edge = stack_peek(tree->unregistered);
        node = edge->right;
    }
    else
        node = tree->root;
    for (int i = common_prefix ; i < length; i++)
    {
            newNode = create_new_Dawg_node(tree->id++);
            tree->size++; // keep tracking the number of nodes
            newEdge = create_new_edge(node, newNode, word[i]);
            node->children[ascii_to_index(word[i])] = newNode;
            stack_push(tree->unregistered, newEdge);
            node = newNode;
    }
    node->isWord = true;
    free(tree->last_word);
    tree->last_word = ft_strdup(word);
}

/**
 * Return new DAWG tree
*/
Dawg    dawg_init()
{
    Dawg tree = (Dawg)malloc(sizeof(struct s_dawg));
    if (!tree)
        exit(EXIT_FAILURE);
    tree->id = 0;
    tree->size = 0;
    tree->last_word =   ft_strdup("");
    tree->root = create_new_Dawg_node(tree->id++);
    tree->registered = (struct hashmap_s *)malloc(sizeof(struct hashmap_s));
    if (hashmap_create(1, tree->registered) != 0)
        exit(EXIT_FAILURE);
    tree->unregistered = new_stack(10000);
    return tree;
}

/**
 * find the word passed as argument in the stored tree 
*/
bool    dawg_search(Dawg tree, char *word)
{
    Dawg_node   current = tree->root;
    int         length;
    int         index;

    parse_word(word);
    length = strlen(word);
    if (!length)return false;
    for (int i=0; i < length; i++)
    {
        index = ascii_to_index(word[i]);
        if (current->children[index] == NULL)
            return false;
        current = current->children[index];
    }
    return (current != NULL && current->isWord);
}

/**
 * Minimizing the tree to depth 0, and deleting the hashmap
*/
void    dawg_finish(Dawg tree)
{
    dawg_minimize(tree, 0);
    hashmap_destroy(tree->registered);
}