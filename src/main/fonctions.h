#ifndef __FONCTIONS_H__
#define __FONCTIONS_H__

/*Prototype*/

/**
 * @brief Function recursive to search a node in the tree according to the tag
 * 
 * @param root root of the tree
 * @param name tag 
 * @param l List of the tokens
 */
void _searchTree(node *root, char *name, _Token **l);

/**
 * @brief Add a new token (node) in the token list 
 * 
 * @param l token list
 * @param n node
 */
void allocateNewToken(_Token **l, node *n);

#endif