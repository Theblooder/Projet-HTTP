#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "verifSemantique.h"


int verificationSemantique(node *root)
{
    
}


/**
 * @brief To clean the request_target with percent_encoding and ".." path
 * 
 * @param dirtyRequest
 * @param len len of the request
 * @param cleanRequest 
 * @return int len of the 
 */
int cleanResquestTarget(const char *dirtyRequest, int len, char *cleanRequest)
{

}

/**
 * @brief Give the path to open a file (end with \0 caracter)
 * 
 * @param absolutePath 
 * @param len len of the absolute path
 * @param destPath 
 * @return char* pointer to the destPath
 */
char *constructAbsolutePath(const char *absolutePath, int len, char *destPath)
{
    char *filesPath = "htdocs";
    destPath = malloc((len + 6 + 1) * sizeof(char));
    char *copyDestPath = destPath;

    /* remove_dot_segment(), percent_encoding_normalization(), */

    strcpy(copyDestPath, filesPath);
    copyDestPath += 6;

    int l = 0;
    while(l < len) {
        *copyDestPath++ = *(absolutePath + l);
        l++;
    }
    *copyDestPath = '\0';

    return destPath;
}

/**
 * @brief search the type of the documents with the lib 
 * 
 * @param absPath 
 * @return int 
 */
int constructContentTypeHeader(char *absPath)
{

}