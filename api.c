#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "api.h"
#include "subroutineParseur.h"
#include "fonctions.h"



#define true 1
#define false 0

static node *root;
static char *requ;
    

int parseur(char *req, int len)
{   
    printf("%d", sizeof(node));
    requ = req;
    root = (node*) malloc(sizeof(node));

    root->pere = NULL;
    root->fils = NULL;
    root->frere = NULL;

    int length;    
    if(length = HTTP_message(0, req, root)) {
        printTree(root, 0, req);
        return true;
    }
    else {
        return false;
    }
}

void *getRootTree()
{
    return root;
}

_Token *searchTree(void *start, char *name)
{
    _Token *l = NULL;
    node *_root;

    if(start == NULL) {
        _root = root;
    }
    else {
        _root = start;
    }

    _searchTree(_root, name, &l);

    return l;
    
}

char *getElementTag(void *n, int *len)
{
}

char *getElementValue(void *n, int *len)
{
    node *_node = n;

    *len = _node->length;

    return &requ[_node->pStart];
}

void purgeElement(_Token **r)
{
    _Token *precedent = NULL;
    _Token *actuel = *r;

    while(actuel != NULL) {
        precedent = actuel;
        actuel = actuel->next;

        free(precedent);
        precedent = NULL;
    }
}

void purgeTree(void *root)
{
    purgeNode(root);
}