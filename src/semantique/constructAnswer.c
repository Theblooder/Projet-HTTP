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
#include "constructAnswer.h"
#include "Answer.h"
#include "serverConf.h"
#include "fastcgi.h"
#include "socket_1.h"

#include "magic.h"

static int method;
static File *f;
static message *requete;
static node *treeRoot;
static int version;


int verificationSemantique(char *reason)
{
    /* Verification of the version number + need to have host header if >= 1.1 */

    _Token *t1,*t2;
    node *versionMajorNode, *versionMinorNode;

    t1 = searchTree(treeRoot, "HTTP_version");
    t2 = searchTree(t1->node, "__digit"); purgeElement(&t1);
    versionMajorNode = t2->node; versionMinorNode = t2->next->node; purgeElement(&t2);

    version = (requete->buf[versionMajorNode->pStart] - 48) * 10 + (requete->buf[versionMajorNode->pStart] - 48);

    if(version >= 20) {
        strcpy(reason, "HTTP Version Not Supported");
        return 505;
    }
    if(version >= 11) {
        _Token *t3;

        t3 = searchTree(treeRoot, "Host_header");
        if(t3 == NULL) {
            strcpy(reason, "Bad Request");
            return 400;
        }
        purgeElement(&t3);
        
    }

    /* To verify that the method is one we implemente */
    _Token *t;
    node * nodeMethod;

    t = searchTree(treeRoot, "method");
    nodeMethod = t->node; purgeElement(&t);
    char *charMethod = &requete->buf[nodeMethod->pStart];

    if(!strncmp(charMethod, "GET", nodeMethod->length)) {
        method = GET;
    }
    else if(!strncmp(charMethod, "HEAD", nodeMethod->length)) {
        method = HEAD;
    }
    else if(!strncmp(charMethod, "POST", nodeMethod->length)) {
        method = POST;
    }
    else {
        strcpy(reason, "Not Implemented");
        return 501;
    }

    return 0;
}

int constructAnswer(node *root, message *req, char *reason, int *versionHTTP)
{
    /* Mettre des define pour la method dans verificationSemantique() + vérifier que si version 1.1 alors doit avoir host header*/
    f = malloc(sizeof(File));
    requete = req;
    treeRoot = root;

    char reasonPrase[MAX_REASON_PHRASE];
    int error;
    if((error = verificationSemantique(reasonPrase)) != 0) {
        *versionHTTP = version;
        strcpy(reason, reasonPrase);
        free(f);
        return error;
    }
    *versionHTTP = version;

    

    /*If GET or HEAD we construct the headrs*/
    if(method == GET | method == HEAD) {
        constructAbsolutePath();

        int res1 = constructContentTypeHeader();
        if(res1 == -1) {
            strcpy(reason, "Not Found");
            free(f->filePath);
            free(f);
            return 404;
        }
        else if(res1 == -2) {
            strcpy(reason, "Error LibMagic");
            free(f->filePath);
            free(f);
            return 500;
        }

        if(res1 == PHP) {
            char contentType[128];
            char *messageBody;
            int contentLength = 0;
            char *forFreeMessageBody;
            char responsePhrase[MAX_REASON_PHRASE];
            _Token *t1;
            node *referer;

            _Token *t2;
            node *query;
            char *queryC = NULL;
            int queryL = 0;
            t2 = searchTree(treeRoot, "query");
            if(t2 != NULL) {
                query = t2->node; purgeElement(&t2);
                queryC = &requete->buf[query->pStart];
                queryL = query->length;
            }

            int res2 = getResultFromPHPInterpreter(&messageBody, contentType, &contentLength, f->filePath, "GET", &forFreeMessageBody, responsePhrase, NULL, 0, queryC, queryL, NULL, 0, NULL, 0, NULL, 0);

            if(res2 == 200) {
                char headerLength[32];
                sprintf(headerLength, "Content-Length: %d\r\n", contentLength);
                constructHeader(headerLength, strlen(headerLength));
                constructHeader(contentType, strlen(contentType));

                if(method == GET) {
                    constructMessageBody(messageBody, contentLength, 1);
                }
                free(forFreeMessageBody);
            }
            else {
                strncpy(reason, responsePhrase, strlen(responsePhrase));
                free(f->filePath);
                free(f);
                return res2;
            }

        }
        else {
            /* To get all the information of the file (! It can open it because its after the the libMagic use) need to be do after the function constructAbsolutePath */
            int file;
            file = open(f->filePath, O_RDONLY);
            fstat(file, &f->st);
            f->addr = mmap(NULL, f->st.st_size, PROT_WRITE, MAP_PRIVATE, file, 0);
            close(file);

            constructContentLengthHeader();


            /*If GET we need to put the body*/
            if(method == GET) {
                constructMessageBody(f->addr, f->st.st_size, 0);
            }
        }
    }
    if(method == POST) {
        constructAbsolutePath();

        int res1 = constructContentTypeHeader();
        if(res1 == -1) {
            strcpy(reason, "Not Found");
            free(f->filePath);
            free(f);
            return 404;
        }
        else if(res1 == -2) {
            strcpy(reason, "Error LibMagic");
            free(f->filePath);
            free(f);
            return 500;
        }

        if(res1 == PHP) {
            char contentType[128];
            char *messageBody;
            int contentLength = 0;
            char *forFreeMessageBody;
            char responsePhrase[MAX_REASON_PHRASE];

            _Token *t1;
            node *referer;
            t1 = searchTree(treeRoot, "Referer");
            referer = t1->node; purgeElement(&t1);

            _Token *t2;
            node *contLength;
            t2 = searchTree(treeRoot, "Content_Length");
            contLength = t2->node; purgeElement(&t2);

            _Token *t3;
            node *contType;
            t3 = searchTree(treeRoot, "Content_Type");
            contType = t3->node; purgeElement(&t3);

            _Token *t4;
            node *messBody;
            t4 = searchTree(treeRoot, "message_body");
            messBody = t4->node; purgeElement(&t4);


            int res2 = getResultFromPHPInterpreter(&messageBody, contentType, &contentLength, f->filePath, "POST", &forFreeMessageBody, responsePhrase, &requete->buf[referer->pStart], referer->length, NULL, 0, &requete->buf[contLength->pStart], contLength->length, &requete->buf[contType->pStart], contType->length, &requete->buf[messBody->pStart], messBody->length);

            if(res2 == 200) {
                char headerLength[32];
                sprintf(headerLength, "Content-Length: %d\r\n", contentLength);
                constructHeader(headerLength, strlen(headerLength));
                constructHeader(contentType, strlen(contentType));

                constructMessageBody(messageBody, contentLength, 1);
                free(forFreeMessageBody);
            }
            else {
                strncpy(reason, responsePhrase, strlen(responsePhrase));
                free(f->filePath);
                free(f);
                return res2;
            }

        }
        else {
            strcpy(reason, "Method Not Allowed");
            free(f->filePath);
            free(f);
            return 405;
        }
    }



    free(f->filePath);
    free(f);

    strcpy(reason, "OK");
    return 200;
}

int needToCloseConnection()
{
    if(version <= 10) {
        return 1;
    }
    else {
        _Token *t1, *t;
        node *n;

        t1 = searchTree(treeRoot, "connection_option");
        t = t1;
        while(t != NULL) {
            n = t->node;
            if(!strncasecmp(&requete->buf[n->pStart], "close", 5)) {
                purgeElement(&t1);
                return 1;
            }
            if(!strncasecmp(&requete->buf[n->pStart], "keep-alive", 10)) {
                purgeElement(&t1);
                return 0;
            }
            t = t->next;
        }


        if(t1 != NULL); purgeElement(&t1);
        return 0;
    }
}

char *cleanResquestTarget(const char *dirtyRequest, int len, char *cleanRequest){
    cleanRequest = malloc((len + 1 + 20) * sizeof(char)); /* the +1 is for the '\0' at the end */  /* + 20 pour le path par défault*/
    char *tempRequest = malloc((len + 1) * sizeof(char));
    char c;
    char c1;
    char c2;
    int i = 0;
    int j = 0;
    int k = 0;
    while(i<len){
        if(dirtyRequest[i]=='%'){
            c1=dirtyRequest[i+1];
            c2=dirtyRequest[i+2];
            c=read_char(c1)*16 + read_char(c2);
            tempRequest[j]=c;
            i=i+3;
            j++;
        }
        else{
            tempRequest[j]=dirtyRequest[i];
            i++;
            j++;
        }
    }
    tempRequest[j]='\0';
    i = 0;
    while(i<j){
        if(tempRequest[i]=='.'){
            if(tempRequest[i+1]=='.'){
                if(tempRequest[i+2]=='/'){
                    i=i+3;
                }
                else if (tempRequest[i+2]=='\0'){
                    i=i+2;
                }
            }
            else if (tempRequest[i+1]=='/'){
                i=i+2;
            }
            else if (tempRequest[i+1]=='\0'){
                i++;
            }
        }
        if(tempRequest[i]=='/'){
            if (tempRequest[i+1]=='.'){
                if(tempRequest[i+2]=='/'){
                    i=i+2;
                }
                else if (tempRequest[i+2]=='.'){
                    while((k!=0) && (cleanRequest[k]!='/')){
                        k--;
                    }
                    i = i+3;
                }
                else{
                    tempRequest[i+1]=='/';
                    i++;
                }
            }
            else{
                cleanRequest[k] = tempRequest[i];
                i++;
                k++;
                while((tempRequest[i]!='/')&&(tempRequest[i]!='\0')){
                  cleanRequest[k] = tempRequest[i];
                  k++;
                  i++;
                }
            }
        }
    }

    /* !!!! ATTENTION ces deux lignes sont la juste pour que le code marche si le pourcent encoding n'est pas fais, Ã  enlever bien sÃ»r si le code est fait */
    if((k>1)&&(cleanRequest[k-1]=='/')) {
      k--;
    }
    if(k==0) {
      cleanRequest[k]='/';
      k++;
    }

    cleanRequest[k] = '\0';


    /* pourcent_encoding */

    /*a/b%D3/c/../d --> a/b@/d */

    if(!strcmp(cleanRequest, "/")) {
        strcpy(cleanRequest, "/index.html");
    }
    free(tempRequest);

    printf("\nCleanRequest:\n\n%s\n\n\n", cleanRequest);
    return cleanRequest;
}

int read_char(char c){
    int i;
    if(c>=48 && c<=57){
        i=c-48;
    }
    else if (c>= 65 && c <= 70){
        i=c-55;
    }
    return i;
}

int constructAbsolutePath()
{
    _Token *t1,*t2;
    node *absolute_path;

    t1 = searchTree(treeRoot, "request_line");
    t2 = searchTree(t1->node, "absolute_path"); purgeElement(&t1);
    absolute_path = t2->node; purgeElement(&t2);

    char *cleanPath;
    cleanPath = cleanResquestTarget(&requete->buf[absolute_path->pStart], absolute_path->length, cleanPath);
    int l = strlen(cleanPath);

    _Token *t3, *t4;
    node *host;

    t3 = searchTree(treeRoot, "Host");
    t4 = searchTree(t3->node, "host"); purgeElement(&t3);
    char filesPath[MAX_LENGTH_SITE];
    if(t4 == NULL) {
        strcpy(filesPath, DEFAULT_SITE);
        filesPath[strlen(DEFAULT_SITE)] = '\0';
    }
    else {
        host = t4->node; purgeElement(&t4);
        getRepertoryFromHost(filesPath, &requete->buf[host->pStart], host->length);
    }
    

    
    f->filePath = malloc((l + strlen(filesPath) + 1) * sizeof(char));
    char *copyDestPath = f->filePath;



    strcpy(copyDestPath, filesPath);
    copyDestPath += strlen(filesPath);

    int i = 0;
    while(i < l) {
        *copyDestPath++ = *(cleanPath + i);
        i++;
    }
    *copyDestPath = '\0';

    free(cleanPath);

    return 0;
}

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

    /* If php we return PHP (int) and we dont construct the header */

    if(strstr(f->filePath, ".php")) {
        magic_close(magic_cookie);
        return PHP;
    }

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

    sprintf(header, "Content-Length: %d\r\n", f->st.st_size);

    constructHeader(header, strlen(header));

    return 0;
}

int constructHostHeader()
{
    _Token *t1, *t2;
    node *host;

    t1 = searchTree(treeRoot, "Host");
    t2 = searchTree(t1->node, "host"); purgeElement(&t1);
    if(t2 == NULL) {
        return -1;
    }
    host = t2->node; purgeElement(&t2);

    char header[MAX_LENGTH_SITE + 10];

    sprintf(header, "Host: %.*s\r\n", host->length, &requete->buf[host->pStart]);

    constructHeader(header, strlen(header));

    return 0;
}
