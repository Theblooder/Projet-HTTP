#ifndef __VERIFSEMANTIQUE_H__
#define __VERIFSEMANTIQUE_H__

/*Prototype*/

typedef struct file {
    char *filePath;
    char type[64];
    struct stat st;
    char *addr;
} File;

#define GET 100
#define HEAD 101
#define POST 102
#define MAX_REASON_PHRASE 32

int verificationSemantique(char *reason);
int constructAnswer(node *root, message *req, char *reason);
int needToCloseConnection();
int constructAbsolutePath();
char *cleanResquestTarget(const char *dirtyRequest, int len, char *cleanRequest);
int constructContentTypeHeader();
int constructContentLengthHeader();

#endif