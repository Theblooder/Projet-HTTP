#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "tree.h"
#include "verifSemantique.h"
#include "constructAnswer.h"

#include "magic.h"

#include "request.h"

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
 * @brief search the type of the documents with the libmagic
 * 
 * @param absPath 
 * @return int content_type header to add
 */
int constructContentTypeHeader(char *absPath)
{
    const char *mime;
    char mime2[32];
    mime2[0] = '\0';
    magic_t magic_cookie;
	
    /* MAGIC_MIME tells magic to return a mime of the file, 
       but you can specify different things	*/
    magic_cookie = magic_open(MAGIC_MIME_TYPE);
	
    if (magic_cookie == NULL) {
        printf("unable to initialize magic library\n");
        return -1;
    }
    
    if (magic_load(magic_cookie, NULL) != 0) {
        printf("cannot load magic database - %s\n", magic_error(magic_cookie));
        magic_close(magic_cookie);
        return -1;
    }

    int file = open(absPath, O_RDONLY);

    if(file == -1) {
        /* Error file existe pas */
        magic_close(magic_cookie);
        return -1;
    }
    
    mime = magic_descriptor(magic_cookie, file);

    /* If he have text/plain we look at the extension to see if we have .css or .js */

    if(strcmp(mime, "text/plain") == 0) {
        if(strstr(absPath, ".css") != NULL) {
            strcpy(mime2, "text/css");
        }
        else if(strstr(absPath, ".js") != NULL) {
            strcpy(mime2, "text/javascript");
        }
    }
    char header[64];
    strcpy(header, "Content-type: ");
    if(mime2[0] != '\0') {
        strcat(header, mime2);
    }
    else {
        strcat(header, mime);
    }
    strcat(header, "\r\n\0");

    magic_close(magic_cookie);

    constructHeader(header, strlen(header));

    close(file);

    return 0; 
}