#include "dawg.h"

int Common_prefix(char   *word1, char    *word2)
{
    int size;

    size = MIN(strlen(word1), strlen(word2));
    for (int i=0; i < size; i++)
    {
        if (word2[i] != word1[i])
        {
            return i;
        }
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
    char *l;

    key = "";
    l= (char *)malloc(sizeof(char)*2);
    l[0] = label;
    l[1] = '\0';
    key = concat(key, l);
    key = concat(key, "_");
    key = concat(key, ft_itoa(id));
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
        edge = stack_pop(tree->unregistered);
        parent = edge->left;
        child = edge->right;
        label = edge->letter;
        key = get_key(label, child->label, child->isWord);
        newChild = hashmap_get(tree->registered, key, strlen(key));
        if (newChild != NULL)
        {
            parent->children[ascii_to_index(label)] = newChild;
            free(child);
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
    dawg_minimize(tree,common_prefix);
    
    if (!is_stack_empty(tree->unregistered))
    {
        edge = stack_pop(tree->unregistered);
        node = edge->right;
    }else
    {
        node = tree->root;
    }
    printf("\n***Common: %d node: %c\n", common_prefix, node->c);
    for (int i = common_prefix ; i < strlen(word); i++)
    {
        newNode = create_new_Dawg_node(tree->id++);
        printf("---Edge: %c --- %c\n", node->c, word[i]);
        newEdge = create_new_edge(node, newNode, word[i]);
        newNode->c = word[i];
        node->children[ascii_to_index(word[i])] = newNode;
        stack_push(tree->unregistered, newEdge);
        printf("+++pushed to stack:   %c \n", newNode->c);
        node = newNode;
    }
    node->isWord = true;
    free(tree->last_word);
    tree->last_word = ft_strdup(word);
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
    tree->last_word =   ft_strdup("");
    tree->root = create_new_Dawg_node(tree->id++);;
    if (hashmap_create(1, tree->registered) != 0)
    {
        printf("hi2");
        exit(EXIT_FAILURE);
    }
    tree->unregistered = new_stack(200000);
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
        printf("%c -> ", word[i]);
        if (current->children[index] == NULL)
            return false;
        printf("%c    ",current->children[index]->c);
        current = current->children[index];
    }
    return (current != NULL && current->isWord);
}


void    dawg_print(Dawg_node root, int space)
{
    Dawg_node current = root;
    for (int i=0;i < 26; i++)
    {
        if (current->children[i]!= NULL)
            printf("%*c   ",space, i+'a');
    }
    printf("\n");
    for (int i=0;i < 26; i++)
    {
        if (current->children[i]!= NULL)
            dawg_print(current->children[i], space + 5);
    }
}






void    dawg_finish(Dawg tree)
{
    dawg_minimize(tree, 0);
    hashmap_destroy(tree->registered);
}