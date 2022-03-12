#include <stdio.h>
#include <stdlib.h>
#include "tree.h"


void printTree(node *root, int height, const char *req)
{
    
    char value[2800];
    int p = 0;
    for(int i=root->pStart; p<root->length; i++) {
        if(req[i] == '\n' || req[i] == '\r') {
            value[p++] = '_';
        }
        else {
            value[p++] = req[i];
        }
    }
    value[p] = '\0';

    if(root->length != 0) {
        for(int i=0; i<height; i++) {
            printf("    ");
        }
        printf("[%d:%s] = \"%s\"\n", height, root->tag, value);
        //printf("[%d:%s] = \"%.*s\"\n", height, root->tag, root->length, &req[root->pStart]);
        height++;
    }
    if(root->fils != NULL) {
        printTree(root->fils, height, req);

        node *actual = root->fils;
        while(actual->frere != NULL) {
            printTree(actual->frere, height, req);
            actual = actual->frere;
        }
    }
}

void putValueInNode(int startPointeur, int length, char *tag, node *n)
{
	n->pStart = startPointeur;
    n->length = length;
    int i = 0;
    while(tag[i] != '\0') {
        n->tag[i] = tag[i];
        i++;
    }
    n->tag[i] = '\0';
}

node* createRoot()
{
    node *root = (node*) malloc(sizeof(node));

    root->pere = NULL;
    root->fils = NULL;
    root->frere = NULL;
    root->tag[0] = '\0';
    root->pStart = 0;
    root->length = 0;

    return root;
}

node* createFils(node *pere)
{
    node *n = (node*) malloc(sizeof(node));

    n->fils = NULL;
    n->frere = NULL;
    n->pere = pere;
    n->tag[0] = '\0';
    n->pStart = 0;
    n->length = 0;  

    if(pere->fils != NULL) {
        node *actual = pere->fils;
        node *precedent = NULL;

        while(actual->frere != NULL) {
            precedent = actual;
            actual = actual->frere;
        }
        actual->frere = n;
    }
    else {
        pere->fils = n;
    }
    return n;
}

int purgeNodeAndRightFrere(node *pere)
{
    node *actual = pere;
    node *precedent = NULL;

    while(actual->frere != NULL) {
        precedent = actual;
        actual = actual->frere;

        purgeNode(precedent);
    }
    purgeNode(actual);

    return 0;
}

int purgeFilsAndFrere(node *pere)
{
    if(pere->fils != NULL) {
        node *actual = pere->fils;
        node *precedent = NULL;

        purgeFilsAndFrere(pere->fils);

        while(actual->frere != NULL) {
            purgeFilsAndFrere(actual->frere);
            precedent = actual;
            actual = actual->frere;
            
            free(precedent);
            precedent = NULL;
        }
        free(actual);
        actual = NULL;

        pere->fils = NULL;
    }
    return 0;
}

/**
 * Remove a node
 * 
 * @param node 
 * @return int
 */
int purgeNode(node *n)
{
    purgeFilsAndFrere(n);
    if(n->pere != NULL) {
        node *actual = n->pere->fils;
        node *precedent = NULL;

        while(actual->frere != NULL) {
            if(actual == n) {
                if(precedent == NULL) {
                    n->pere->fils = actual->frere;
                }
                else {
                    precedent->frere = actual->frere;
                }
                free(actual);
                actual = NULL;
                return 0;
            }
            precedent = actual;
            actual = actual->frere;
        }
        if(actual == n) {
            if(precedent != NULL) {
                precedent->frere = NULL;
            }
            else {
                n->pere->fils = NULL;
            }
            free(actual);
            actual = NULL;
        }
    }
    else {
        free(n);
        n = NULL;
    }
    return 0;
}