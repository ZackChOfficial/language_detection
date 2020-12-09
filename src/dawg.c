#include "dawg.h"

int Common_prefix(char   *word1, char    *word2)
{
    for (int i=0; word1[i] && word2[i]; i++)
    {
        if (word2[i] != word1[i])
            return i;
    }
    return 0;
}

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
Edge create_new_edge(Dawg_node left, Dawg_node right, char label)
{
    Edge newEdge = (Edge)malloc(sizeof(struct s_edge));
    if (!newEdge)
    {
        printf("hi3");
        exit(EXIT_FAILURE);
    }
    newEdge->left = left;
    newEdge->right = right;
    newEdge->letter = label;
    return newEdge;
}
char    *get_key(char label, int id, bool isWord)
{
    char *key;
    char *tmp;

    key = "";
    printf("get_key: n0 %s\n", key);
    char *l= (char *)malloc(sizeof(char)*2);
    l[0] = label;
    l[1] = '\0';
    key = concat(key, l);
    printf("get_key: n1 %s\n", key);
    key = concat(key, "_");
    printf("get_key: n1.5 %s\n", key);
    sprintf(tmp,"%d",id); // error here
    printf("get_key: n2 %s\n", key);
    key = concat(key, tmp);
    key = concat(key, "_");
    if (isWord)
        key = concat(key, "1");
    else 
        key = concat(key, "0");
    return key;
}
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
        printf("mini: n1\n");
        edge = stack_pop(tree->unregistered);
        printf("mini: n2\n");
        parent = edge->left;
        child = edge->right;
        label = edge->letter;
        printf("mini: n5 \n");
        key = get_key(label, edge->right->label, edge->right->isWord);
        printf("mini: n4 %s\n", key);
        newChild = hashmap_get(tree->registered, key, strlen(key));
        printf("mini: n3\n");
        if (newChild != NULL)
        {
            parent->children[ascii_to_index(label)] = newChild;
        }else
        {
            hashmap_put(tree->registered,key, strlen(key), child);
        }
    }
}

void dawg_insert(Dawg tree, char    *word)
{
    Edge edge;
    Edge newEdge;
    Dawg_node   node;
    Dawg_node newNode;
    int common_prefix = Common_prefix(tree->last_word, word);
    printf("no\n");
    dawg_minimize(tree,common_prefix);
    printf("ss me\n");
    if (!is_stack_empty(tree->unregistered))
    {
        edge = stack_pop(tree->unregistered);
        node = edge->right;
    }else
        node = tree->root;
    for (int i = common_prefix; word[i]; i++)
    {
        printf("no1\n");
        newNode = create_new_Dawg_node(tree->id++);
        printf("no2 %zu %c\n",ascii_to_index(word[i]), word[i]);
        node->children[ascii_to_index(word[i])] = newNode;
        printf("no3\n");
        newEdge = create_new_edge(node, newNode, word[i]);// add data here
        printf("no4\n");
        stack_push(tree->unregistered, newEdge);
    }
    node->isWord = true;
    tree->last_word = word;
}

Dawg    dawg_init()
{
    Dawg tree = (Dawg)malloc(sizeof(struct s_dawg));
    if (!tree)
    {
        printf("hi1");
        exit(EXIT_FAILURE);
    }
    tree->id = 0;
    tree->last_word = "";
    tree->root = create_new_Dawg_node(tree->id++);;
    if (hashmap_create(2, tree->registered) != 0)
    {
        printf("hi2");
        exit(EXIT_FAILURE);
    }
    tree->unregistered = new_stack(10);
    return tree;
}

bool    dawg_search(Dawg tree, char *word)
{
    Dawg_node   current = tree->root;
    int         length = strlen(word);
    int         index;

    for (int i=0; i < length; i++)
    {
        index = ascii_to_index(word[i]);
        if (current->children[index] == NULL)
            return false;
        current = current->children[index];
    }
    return (current != NULL && current->isWord);
}







void    dawg_finish(Dawg tree)
{
    dawg_minimize(tree, 0);
    hashmap_destroy(tree->registered);
}