#ifndef __TREE_H__
#define __TREE_H__

/*Prototype*/

/**
 * @brief Strutur of the parser tree
 * 
 * Every node have 1 fils who have many brothers
 * 
 */
typedef struct node node;

struct node {
	int pStart;     // start of the token
	int length;     // length of the token
	char tag[32];   // tag of the token
	node *fils;     // pointer to his first child
    node *frere;    // pointer to his first brother
    node *pere;     // pointer to his father
};
/**
 * @brief Display the tree of the parser in standard input
 * 
 * @param root Node where we start to display
 * @param _height To put to 0
 * @param req The request passed to the parser
 * 
 */
void printTree(node *root, int _height, const char *req);

/**
 * @brief To put all the value into a node
 * 
 * @param startPointeur start of the request for the token
 * @param length length of the request for the token
 * @param tag tag of the token
 * @param n node to update
 */
void putValueInNode(int startPointeur, int length, char *tag, node *n);

/**
 * @brief Create the root of the tree
 * 
 * @return node* 
 */
node* createRoot();

/**
 * @brief Create a fils of the father
 * 
 * @param pere 
 * @return node* 
 */
node* createFils(node *pere);

/**
 * @brief Purge the node and his right brother
 * 
 * @param pere 
 * @return int 
 */
int purgeNodeAndRightFrere(node *pere);

/**
 * @brief Purge all son of the node
 * 
 * @param pere 
 * @return int 
 */
int purgeFils(node *pere);

/**
 * @brief Purge the node itself
 * 
 * @param noden 
 * @return int 
 */
int purgeNode(node *noden);

#endif