#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>

#include "request.h"

#include "api.h"
#include "tree.h"
#include "verifSemantique.h"
#include "constructAnswer.h"

#include "magic.h"



/**
 * @brief To verify the semantique
 * 
 * @param root root of the tree
 * @param reason if there is an error we say here the reason
 * @return int the number of the error, 0 if None
 */
int verificationSemantique(node *root, message *requete, char *reason)
{
    /* To verify that the method is one we use */
    _Token *t;
    node * nodeMethod;

    t = searchTree(root, "method");
    nodeMethod = t->node; purgeElement(&t);

    char *method = &requete->buf[nodeMethod->pStart];
    return 0;
}

int constructAnswer(node *root, message *requete, char *reason)
{
    _Token *r,*tok;
    node *absolute_path;
    File *f = malloc(sizeof(File));
    int file;
    
    // // get the root of the tree this is no longer opaque since we know the internal type with httpparser.h 
    // //void *root;
    r = searchTree(root, "request_line"); 
    tok = searchTree(r->node, "absolute_path"); purgeElement(&r);
    absolute_path = tok->node; purgeElement(&tok);
    
    constructAbsolutePath(&requete->buf[absolute_path->pStart], absolute_path->length, f);

    
    if(constructContentTypeHeader(f) == -1) {
        strcpy(reason, "Not Found");
        free(f->filePath);
        free(f);
        return 404;
    }
    file = open(f->filePath, O_RDONLY);

    fstat(file, &f->st);
    f->addr = mmap(NULL, f->st.st_size, PROT_WRITE, MAP_PRIVATE, file, 0);
    close(file);

    constructContentLengthHeader(f);




    constructMessageBody(f->addr, f->st.st_size, 0);
    


    free(f->filePath);
    free(f);

    return 0;
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
 * @return int 0 if ok -1 if error (ne need now to verify it)
 */
int constructAbsolutePath(const char *absolutePath, int len, File *f)
{
    char *filesPath = "htdocs";
    f->filePath = malloc((len + 6 + 1) * sizeof(char));
    char *copyDestPath = f->filePath;

    /* remove_dot_segment(), percent_encoding_normalization(), */

    strcpy(copyDestPath, filesPath);
    copyDestPath += 6;

    int l = 0;
    while(l < len) {
        *copyDestPath++ = *(absolutePath + l);
        l++;
    }
    *copyDestPath = '\0';

    return 0;
}

/**
 * @brief search the type of the documents with the libmagic
 * 
 * @param absPath 
 * @return int content_type header to add (-1 if file not find, -2 if libmagic didn't work)
 */
int constructContentTypeHeader(File *f)
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
        return -2;
    }
    
    if (magic_load(magic_cookie, NULL) != 0) {
        printf("cannot load magic database - %s\n", magic_error(magic_cookie));
        magic_close(magic_cookie);
        return -2;
    }

    int file = open(f->filePath, O_RDONLY);

    if(file == -1) {
        /* Error file existe pas */
        magic_close(magic_cookie);
        return -1;
    }
    
    mime = magic_descriptor(magic_cookie, file);

    /* If he have text/plain we look at the extension to see if we have .css or .js */

    if(strcmp(mime, "text/plain") == 0) {
        if(strstr(f->filePath, ".css") != NULL) {
            strcpy(mime2, "text/css");
        }
        else if(strstr(f->filePath, ".js") != NULL) {
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

int constructContentLengthHeader(File *f)
{
    char header[32];
    
    sprintf(header, "Content-Length: %d\r\n\0", f->st.st_size);

    constructHeader(header, strlen(header));

    return 0;
}