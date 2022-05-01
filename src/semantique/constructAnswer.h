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

#define MAX_REASON_PHRASE 32

int verificationSemantique(char *reason);
int constructAnswer(node *root, message *req, char *reason, int *versionHTTP);
int needToCloseConnection();
int constructAbsolutePath();
char *cleanResquestTarget(const char *dirtyRequest, int len, char *cleanRequest);
int constructContentTypeHeader();
int constructContentLengthHeader();

/**
 * @brief if there is no host, none will be added
 * 
 * @return int -1 if no host
 */
int constructHostHeader();  

#endif