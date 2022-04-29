#ifndef __VERIFSEMANTIQUE_H__
#define __VERIFSEMANTIQUE_H__

/*Prototype*/

typedef struct file {
    char *filePath;
    char type[64];
    struct stat st;
    char *addr;
} File;

int verificationSemantique(node *root, message *requete, char *reason);
int constructAnswer(node *root, message *requete, char *reason);
int constructAbsolutePath(const char *absolutePath, int len, File *f);
int cleanResquestTarget(const char *dirtyRequest, int len, char *cleanRequest);
int constructContentTypeHeader(File *f);
int constructContentLengthHeader(File *f);

#endif