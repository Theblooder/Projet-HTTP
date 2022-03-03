#include <stdio.h>
#include <stdlib.h>
#include "../tree.h"
#include "subroutineMultipleTerminal.h"
#include "headerAcceptEncoding.h"
#include "headerAccept.h"


#define true 1
#define false 0

int Accept_Encoding_header(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_string(now, req, fils = createFils(pere), "Accept-Encoding"))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), ':'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = OWS(now, req, fils = createFrere(fils)))) {
        purgeFilsAndFrere(fils);
    }
    else {
        fils = createFrere(fils);
    }
    now += len;

    if(!(len = Accept_Encoding(now, req, fils))) {
        purgeNode(fils);
    }
    now += len;

    if(!(len = OWS(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
    }
    now += len;

    putValueInNode(p, now-p, "Accept_Encoding_header", pere);
    return now-p;
}

int Accept_Encoding(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node *fils;

    if(!(len = __accept_Encoding__1(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    int nbr = 0;
    while(len = __accept_Encoding__2(now, req, fils = createFrere(fils))) {
        nbr++;
        now += len;
    }
    purgeFilsAndFrere(fils);
    purgeNode(fils);

    putValueInNode(p, now-p, "Accept_Encoding", pere);
    return now-p;
}

int __accept_Encoding__1(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    if(len = case_insensitive_char(p, req, fils = createFils(pere), ',')) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = codings__AND__weight(p, req, fils)) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeNode(fils);
        
    return false;
}

int codings__AND__weight(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = codings(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = weight(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int codings(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    if(len = content_coding(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "codings", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = case_insensitive_string(p, req, fils, "identity")) {
        putValueInNode(p, len, "codings", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = case_insensitive_char(p, req, fils, '*')) {
        putValueInNode(p, len, "codings", pere);
        return len;
    }
    else
        purgeNode(fils);
        
    return false;
}

int content_coding(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = token(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "content_coding", pere);
    return now-p;
}

int __accept_Encoding__2(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = OWS(now, req, fils = createFils(pere)))) {
        purgeFilsAndFrere(fils);
    }
    else {
        fils = createFrere(fils);
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils, ','))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = optional__accept_Encoding__2(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int optional__accept_Encoding__2(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = OWS(now, req, fils = createFils(pere)))) {
        purgeFilsAndFrere(fils);
    }
    else {
        fils = createFrere(fils);
    }
    now += len;

    if(!(len = codings__AND__weight(now, req, fils))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}