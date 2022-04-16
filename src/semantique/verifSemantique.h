#ifndef __VERIFSEMANTIQUE_H__
#define __VERIFSEMANTIQUE_H__

/*Prototype*/

int verificationSemantique(node *root);
char *constructAbsolutePath(const char *absolutePath, int len, char *destPath);
int cleanResquestTarget(const char *dirtyRequest, int len, char *cleanRequest);
int constructContentTypeHeader(char *absPath);

#endif