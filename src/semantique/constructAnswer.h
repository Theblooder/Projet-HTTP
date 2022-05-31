#ifndef __VERIFSEMANTIQUE_H__
#define __VERIFSEMANTIQUE_H__

/*Prototype*/

/**
 * @brief To store all the information about a file
 * 
 */
typedef struct file {
    char *filePath;   /* The path of the file */
    char type[64];    /* type MIME */
    struct stat st;   /* stats thanks to stat() */
    char *addr;       /* The address thanks to nmap() */
} File;

#define GET 100
#define HEAD 101
#define POST 102

#define PHP 1000

#define MAX_REASON_PHRASE 32

/**
 * @brief To verify some semantic rules
 * 
 * @param reason if error we say the reason
 * @return int 
 */
int verificationSemantique(char *reason);

/**
 * @brief main function to construct the header
 * 
 * @param root root of the tree parser
 * @param req requete
 * @param reason
 * @param versionHTTP
 * @return int 
 */
int constructAnswer(node *root, message *req, char *reason, int *versionHTTP);

/**
 * @brief return 1 if the connection need to be closed 0 else
 * 
 * @return int 
 */
int needToCloseConnection();

/**
 * @brief to get the path of the file (after removing dot segment and make the purcent encoding)
 * 
 * @return int 
 */
int constructAbsolutePath();

/**
 * @brief purcent encoding and removing dot segment (not implemented yet)
 * 
 * @param dirtyRequest 
 * @param len length of the dirty request
 * @param cleanRequest 
 * @return char* return the clean request
 */
char *cleanResquestTarget(const char *dirtyRequest, int len, char *cleanRequest);

/**
 * @brief construct the content-type header, search the type of the documents with the libmagic
 * 
 * @return int -1 if file not find, -2 if libmagic don't work
 */
int constructContentTypeHeader();

/**
 * @brief construct the content-length header
 * 
 * @return int 
 */
int constructContentLengthHeader();

/**
 * @brief if there is no host, none will be added
 * 
 * @return int -1 if no host
 */
int constructHostHeader();  

int read_char(char c);

#endif
