#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constructAnswer.h"
#include "magic.h"

#include "request.h"


static Answer *AnswerToClient = NULL;

void initAnswer(int clientID)
{
    if(AnswerToClient != NULL) {
        purgeAnswer();
    }
    AnswerToClient = (Answer*) malloc(sizeof(Answer));

    AnswerToClient->bufSL = NULL;
    AnswerToClient->bufMB = NULL;
    AnswerToClient->lenSL = 0;
    AnswerToClient->lenMB = 0;
    AnswerToClient->headers = NULL;

    AnswerToClient->isMBallocate = 0;

    AnswerToClient->clientID = clientID;
}

void purgeAnswer()
{
    if(AnswerToClient != NULL) {
        free(AnswerToClient->bufSL);
        AnswerToClient->bufSL = NULL;

        Header *h = AnswerToClient->headers;
        Header *prec = NULL;
        while(h != NULL) {
            free(h->buf);
            h->buf = NULL;
            prec = h;
            h = h->next;
            free(prec);
            prec = NULL;
        }

        if(AnswerToClient->isMBallocate) {
            free(AnswerToClient->bufMB);
        }
        AnswerToClient->bufMB = NULL;

        free(AnswerToClient);
        AnswerToClient = NULL;
    }
}


int sendAnswerToClient()
{
        writeDirectClient(AnswerToClient->clientID, AnswerToClient->bufSL, AnswerToClient->lenSL);
    printf("%.*s", AnswerToClient->lenSL, AnswerToClient->bufSL);

    Header *h = AnswerToClient->headers;
    while(h != NULL) {
        writeDirectClient(AnswerToClient->clientID, h->buf, h->len);
        printf("%.*s", h->len, h->buf);
        h = h->next;
    }
    writeDirectClient(AnswerToClient->clientID, "\r\n", 2);
    writeDirectClient(AnswerToClient->clientID, AnswerToClient->bufMB, AnswerToClient->lenMB);
    printf("\r\n%.*s\n", AnswerToClient->lenMB, AnswerToClient->bufMB);

    endWriteDirectClient(AnswerToClient->clientID);
    
    return 0;
}

int constructFirstLine(char *httpVersion, int statusCode, char *reasonPhrase)
{
    int lenTotal = 0;

    lenTotal += (13 + strlen(reasonPhrase) + 2);

    if(!AnswerToClient->lenSL) {
        AnswerToClient->bufSL = malloc(lenTotal * sizeof(char));
    }
    else {
        char *tmp = realloc(AnswerToClient->bufSL, lenTotal);
        if(tmp == NULL) {
            AnswerToClient->lenSL = 0;
            free(AnswerToClient->bufSL);
            AnswerToClient->bufSL = NULL;
            printf("Error : realocation failed\n");
            return -1;
        }
        else {
            AnswerToClient->bufSL = tmp;
        }
    }
    AnswerToClient->lenSL = lenTotal;

    char *cpy = AnswerToClient->bufSL;

    *(cpy++) = 'H'; *(cpy++) = 'T'; *(cpy++) = 'T'; *(cpy++) = 'P'; *(cpy++) = '/'; *(cpy++) = httpVersion[0]; *(cpy++) = httpVersion[1]; *(cpy++) = httpVersion[2];

    cpy += sprintf(cpy, " %d ", statusCode);

    int i = 0;
    while(reasonPhrase[i]) {
        *(cpy++) = reasonPhrase[i++];
    }
    *(cpy++) = '\r'; *(cpy++) = '\n';
    return 0;
}

int constructHeader(char *header, int len)
{
    Header *h = AnswerToClient->headers;
    h = (Header*) malloc(sizeof(Header));

    h->next = AnswerToClient->headers;
    h->buf = (char*) malloc(len * sizeof(char));
    AnswerToClient->headers = h;
    h->len = len;

    for(int i=0; i<len; i++) {
        h->buf[i] = header[i];
    }
    return 0;
}

int constructMessageBody(char *message, int len, int needToAllocate)
{
    if(needToAllocate) {
        if(!AnswerToClient->lenMB) {
            AnswerToClient->bufMB = malloc(len * sizeof(char));
        }
        char *tmp = realloc(AnswerToClient->bufMB, len);
        if(tmp == NULL) {
            AnswerToClient->lenMB = 0;
            free(AnswerToClient->bufMB);
            AnswerToClient->bufMB = NULL;
            printf("Error : realocation failed\n");
            return -1;
        }
        else {
            AnswerToClient->bufMB = tmp;
        }

        for(int i=0; i<len; i++) {
            AnswerToClient->bufMB[i] = message[i];
        }

        AnswerToClient->isMBallocate = 1;
    }
    else {
        if(AnswerToClient->isMBallocate) {
            free(AnswerToClient->bufMB);
        }
        AnswerToClient->bufMB = message;
        AnswerToClient->isMBallocate = 0;
    }
    AnswerToClient->lenMB = len;

    return 0;
}