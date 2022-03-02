#include <stdio.h>
#include <stdlib.h>
#include "../tree.h"
#include "subroutineParseur.h"
#include "subroutineMultipleTerminal.h"
#include "subroutineFirstLine.h"

#include "headerConnection.h"
#include "headerContentLength.h"
#include "headerContentType.h"
#include "headerCookie.h"
#include "headerTransfertEncoding.h"
#include "headerExpect.h"
#include "headerHost.h"
#include "headerAccept.h"


#define true 1
#define false 0


int HTTP_message(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = start_line(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    int nbr = 0;
    while(len = header_field__AND__CRLF(now, req, fils = createFrere(fils))) {
        nbr++;
        now += len;
    }
    purgeFilsAndFrere(fils);

    if(!(len = CRLF(now, req, fils))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = message_body(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
    }
    now += len;

    putValueInNode(p, now-p, "HTTP_message", pere);
    return now-p;
}

int header_field__AND__CRLF(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = header_field(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = CRLF(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int header_field(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    if(len = Connection_header(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "header_field", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = Content_Length_Header(p, req, fils)) {
        putValueInNode(p, len, "header_field", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = Content_Type_header(p, req, fils)) {
        putValueInNode(p, len, "header_field", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = Cookie_header(p, req, fils)) {
        putValueInNode(p, len, "header_field", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = Transfer_Encoding_header(p, req, fils)) {
        putValueInNode(p, len, "header_field", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = Expect_header(p, req, fils)) {
        putValueInNode(p, len, "header_field", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = Host_header(p, req, fils)) {
        putValueInNode(p, len, "header_field", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = Accept_header(p, req, fils)) {
        putValueInNode(p, len, "header_field", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    return false;

    if(len = Unknow_header(p, req, fils)) {
        putValueInNode(p, len, "header_field", pere);
        return len;
    }
    else
        purgeNode(fils);
        
    return false;
}


int message_body(int p, const char *req, node *pere)
{
    int len;
    int now = p;
    node *fils;

    int nbr = 0;
    fils = createFils(pere);
    while(len = OCTET(now, req, fils)) {
        nbr++;
        now += len;
        fils = createFrere(fils);
    }
    purgeFilsAndFrere(fils);
    purgeNode(fils);

    putValueInNode(p, now-p, "message_body", pere);
    return now-p;
}





/*==============================================================*/

/*
int message(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = debut(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }

    now += len;

    int nbr = 0;
    while(len = corps(now, req, fils = createFrere(fils))) {
        nbr++;
        now += len;
    }
    purgeFilsAndFrere(fils);
    if(nbr < 2) {
        return false;
    }

    if(!(len = ponctuation(now, req, fils))) {
        purgeFilsAndFrere(fils);
    }
    else {
        fils = createFrere(fils);
    }

    now += len;

    if(!(len = fin(now, req, fils))) {
        purgeNode(fils);
        return false;
    }
    
    now += len;

    if(!(len = caseInsensitive(now, req, '\n', fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }


    now += len;

    putValueInNode(p, now-p, "message", pere);

    return now-p;
}

int debut(int p, const char *req, node *pere)
{
    int now = p;
    if(req[now] == 's' || req[now] == 'S') {
        now++;
        if(req[now] == 't' || req[now] == 'T') {
            now++;
            if(req[now] == 'a' || req[now] == 'A') {
                now++;
                if(req[now] == 'r' || req[now] == 'R') {
                    now++;
                    if(req[now] == 't' || req[now] == 'T') {
                        putValueInNode(p, 5, "debut", pere);
                        return 5;
                    }
                }
            }
        }
    }
    return false;
}

int corps(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    if(len = corps1(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "corps", pere);
        return len;
    }
    else
        purgeNode(fils);

    if(len = corps2(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "corps", pere);
        return len;
    }
    else
        purgeNode(fils);
        
    return false;
}

int corps1(int p, const char *req, node *pere)
{
    int len;
    int now = p;
    node *fils;

    if(!(len = mot(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }

    now += len;

    if(!(len = ponctuation(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }

    now += len;

    putValueInNode(p, now-p, "corps1", pere);
    return now-p;
}

int corps2(int p, const char *req, node *pere)
{
    int len;
    int now = p;
    node *fils;

    if(!(len = nombre(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }

    now += len;

    if(!(len = separateur(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }

    now += len;

    putValueInNode(p, now-p, "corps2", pere);
    return now-p;
}

int mot(int p, const char *req, node *pere)
{
    int len;
    int now = p;
    node *fils;

    int nbr = 0;
    fils = createFils(pere);
    while(len = alpha(now, req, fils)) {
        nbr++;
        now += len;
        fils = createFrere(fils);
    }
    purgeFilsAndFrere(fils);
    if(nbr == 0) {
        return false;
    }

    if(!(len = separateur(now, req, fils))) {
        purgeNode(fils);
        return false;
    }

    now += len;

    putValueInNode(p, now-p, "mot", pere);
    return now-p;
}

int nombre(int p, const char *req, node *pere)
{
    int len;
    int now = p;
    node *fils;

    int nbr = 0;
    fils = createFils(pere);
    while(len = digit(now, req, fils)) {
        nbr++;
        now += len;
        fils = createFrere(fils);
    }
    purgeFilsAndFrere(fils);
    purgeNode(fils);
    if(nbr == 0) {
        return false;
    }
    
    putValueInNode(p, now-p, "nombre", pere);
    return now-p;
}

*/