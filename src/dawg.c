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
    return size;
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

char    *get_key(Dawg_node node)
{
    char *key;
    char *tmp;
    char *l;

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

void dawg_minimize(Dawg tree, int depth)
{
    Edge        edge;
    Dawg_node   parent;
    Dawg_node   child;
    Dawg_node   newChild;
    char        label;
    char        *key;

    //printf("stack size: %d   top: %c\n", stack_size(tree->unregistered), (stack_size(tree->unregistered) > 0 ? ((Edge)stack_peek(tree->unregistered))->letter : '*'));
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
            tree->size--;
        }else
        {
            hashmap_put(tree->registered,key, strlen(key), child);
        }
    }
    //printf("stack size: %d   top: %c\n", stack_size(tree->unregistered), (stack_size(tree->unregistered) > 0 ? ((Edge)stack_peek(tree->unregistered))->letter : '*'));
}

void dawg_insert(Dawg tree, char    *word)
{
    Edge edge;
    Edge newEdge;
    Dawg_node   node;
    Dawg_node newNode;

    //printf("-------------------------------\n");
    int common_prefix = Common_prefix(tree->last_word, word);
    dawg_minimize(tree,common_prefix);
    // printf("common: %s   -> %d <-  %s\n", tree->last_word, common_prefix, word);
    if (!is_stack_empty(tree->unregistered))
    {
        edge = stack_peek(tree->unregistered);
        node = edge->right;
    }else
    {
        node = tree->root;
    }

    for (int i = common_prefix ; i < strlen(word); i++)
    {
        if (word[i] >= 'a' && word[i] <= 'z')
        {
            newNode = create_new_Dawg_node(tree->id++);
            tree->size++;
            newEdge = create_new_edge(node, newNode, word[i]);
            // newNode->c = word[i];
            node->children[ascii_to_index(word[i])] = newNode;
            //printf("    from: %c-%d to -> %c-%d\n", node->c, node->label, newNode->c, newNode->label);
            //printf("    --| stack size: %d   top: %c\n", stack_size(tree->unregistered), (stack_size(tree->unregistered) > 0 ? ((Edge)stack_peek(tree->unregistered))->letter : '*'));
            stack_push(tree->unregistered, newEdge);
            //printf("    ++| stack size: %d   top: %c\n", stack_size(tree->unregistered), (stack_size(tree->unregistered) > 0 ? ((Edge)stack_peek(tree->unregistered))->letter : '*'));
            node = newNode;
        }
    }
    //printf("---------------------------------\n\n");
    newNode->isWord = true;
    free(tree->last_word);
    tree->last_word = NULL;
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
    tree->size = 0;
    tree->last_word =   ft_strdup("");
    tree->root = create_new_Dawg_node(tree->id++);
    tree->registered = (struct hashmap_s *)malloc(sizeof(struct hashmap_s));
    if (hashmap_create(1, tree->registered) != 0)
    {
        printf("hi2");
        exit(EXIT_FAILURE);
    }
    tree->unregistered = new_stack(10000);
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
        // printf("%c -> ", word[i]);
        if (current->children[index] == NULL)
            return false;
        // printf("%c    ",current->children[index]->c);
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