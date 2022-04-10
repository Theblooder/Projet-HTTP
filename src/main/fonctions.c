#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "api.h"
#include "fonctions.h"


#define true 1
#define false 0

void _searchTree(node *root, char *name, _Token **l)
{
    if(!strcmp(root->tag, name)) {
        allocateNewToken(l, root);

    }
    if(root->fils != NULL) {
        _searchTree(root->fils, name, l);

        node *actual = root->fils;
        while(actual->frere != NULL) {
            _searchTree(actual->frere, name, l);
            actual = actual->frere;
        }
    }
}

void allocateNewToken(_Token **l, node *n)
{
    _Token *precedent = NULL;
    _Token *actuel = *l;

    _Token *e = (_Token*) malloc(sizeof(_Token));
    e->node = n;
    e->next = NULL;


    while(actuel != NULL) {
        precedent = actuel;
        actuel = actuel->next;
    }

    if(precedent == NULL) {
        *l = e;
    }
    else {
		precedent->next = e;
    }
}