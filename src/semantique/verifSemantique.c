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

static int method;
static File *f;
static message *requete;
static node *treeRoot;

/**
 * @brief To verify the semantique
 *
 * @param root root of the tree
 * @param reason if there is an error we say here the reason
 * @return int the number of the error, 0 if None
 */
int verificationSemantique(node *root, message *req, char *reason)
{
    /* To verify that the method is one we use */
    _Token *t;
    node * nodeMethod;

    t = searchTree(root, "method");
    nodeMethod = t->node; purgeElement(&t);
    char *charMethod = &req->buf[nodeMethod->pStart];

    if(!strncmp(charMethod, "GET", 3)) {
        method = GET;
    }
    else if(!strncmp(charMethod, "HEAD", 4)) {
        method = HEAD;
    }
    else if(!strncmp(charMethod, "POST", 4)) {
        method = POST;
    }
    else {
        strcpy(reason, "Not Implemented");
        return 501;
    }

    return 0;
}

int constructAnswer(node *root, message *req, char *reason)
{
    /* Mettre des define pour la method dans verificationSemantique() + vérifier que si version 1.1 alors doit avoir host header*/
    f = malloc(sizeof(File));
    requete = req;
    treeRoot = root;


    _Token *r,*tok;
    node *absolute_path;
    
    int file;

    r = searchTree(root, "request_line");
    tok = searchTree(r->node, "absolute_path"); purgeElement(&r);
    absolute_path = tok->node; purgeElement(&tok);

    /*Si GET ou HEAD alors on fait tout ca*/
    if(method == GET | method == HEAD) {
        constructAbsolutePath(&requete->buf[absolute_path->pStart], absolute_path->length);


        if(constructContentTypeHeader() == -1) {
            strcpy(reason, "Not Found");
            free(f->filePath);
            free(f);
            return 404;
        }
        file = open(f->filePath, O_RDONLY);

        fstat(file, &f->st);
        f->addr = mmap(NULL, f->st.st_size, PROT_WRITE, MAP_PRIVATE, file, 0);
        close(file);

        constructContentLengthHeader();


        /*Si Get faut faire ca*/
        if(method == GET) {
            constructMessageBody(f->addr, f->st.st_size, 0);
        }
    }



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
char *cleanResquestTarget(const char *dirtyRequest, int len, char *cleanRequest)
{
    cleanRequest = malloc((len + 1) * sizeof(char)); /* the +1 is for the '\0' at the end */


    /* !!!! ATTENTION ces deux lignes sont la juste pour que le code marche si le pourcent encoding n'est pas fais, à enlever bien sûr si le code est fait */
    strncpy(cleanRequest, dirtyRequest, len);
    cleanRequest[len] = '\0';


    /* pourcent_encoding */

    /*a/b%D3/c/../d --> a/b@/d */


    return cleanRequest;
}

/**
 * @brief Give the path to open a file (end with \0 caracter)
 *
 * @param absolutePath
 * @param len len of the absolute path
 * @param destPath
 * @return int 0 if ok -1 if error (ne need now to verify it)
 */
int constructAbsolutePath(const char *absolutePath, int len)
{
    char *filesPath = "htdocs";

    char *cleanPath;
    cleanPath = cleanResquestTarget(absolutePath, len, cleanPath);
    int l = strlen(cleanPath);

    f->filePath = malloc((l + 6 + 1) * sizeof(char));
    char *copyDestPath = f->filePath;



    strcpy(copyDestPath, filesPath);
    copyDestPath += 6;

    int i = 0;
    while(i < len) {
        *copyDestPath++ = *(cleanPath + i);
        i++;
    }
    *copyDestPath = '\0';

    free(cleanPath);

    return 0;
}

/**
 * @brief search the type of the documents with the libmagic
 *
 * @param absPath
 * @return int content_type header to add (-1 if file not find, -2 if libmagic didn't work)
 */
int constructContentTypeHeader()
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

int constructContentLengthHeader()
{
    char header[32];

    sprintf(header, "Content-Length: %d\r\n\0", f->st.st_size);

    constructHeader(header, strlen(header));

    return 0;
}
