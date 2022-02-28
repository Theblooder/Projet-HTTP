#ifndef __TREE_H__
#define __TREE_H__

/*Prototype*/

typedef struct node node;

struct node {
	int pStart;
	int length;
	char tag[32];
	node *fils;
    node *frere;
    node *pere;
};


void printTree(node *root, int height, const char *req);
void putValueInNode(int startPointeur, int length, char *tag, node *n);
node* createFils(node *pere);
node* createFrere(node *frere);
int purgeFilsAndFrere(node *pere);
int purgeNode(node *noden);

#endif