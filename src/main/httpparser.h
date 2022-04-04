// typedef struct node {
// 		int level; 
// 		char *name;
// 		char *value ;
// 		int len;
// 		int explored;
// 		struct node *link;
// 		} Lnode ;

typedef struct node {
	int pStart;     // start of the token
	int length;     // length of the token
	char tag[32];   // tag of the token
	struct Lnode *fils;     // pointer to his first child
    struct Lnode *frere;    // pointer to his first brother
    struct Lnode *pere;     // pointer to his father
} Lnode;

