#include <stdio.h>
#include <stdlib.h>
#include "../main/tree.h"
#include "subroutineMultipleTerminal.h"
#include "headerAcceptCharset.h"
#include "headerAccept.h"


#define true 1
#define false 0

int Accept_Charset_header(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_string(now, req, fils = createFils(pere), "Accept-Charset"))) {
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

    if(!(len = Accept_Charset(now, req, fils))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = OWS(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
    }
    now += len;

    putValueInNode(p, now-p, "Accept_Charset_header", pere);
    return now-p;
}

int Accept_Charset(int p, const char *req, node *pere)
{
    int len;
    int now = p;
    node *fils;

    int nbr = 0;
    fils = createFils(pere);
    while(len = case__AND__OWS(now, req, fils)) {
        nbr++;
        now += len;
        fils = createFrere(fils);
    }
    purgeFilsAndFrere(fils);

    if(!(len = __accept_Charset__2(now, req, fils))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    nbr = 0;
    while(len = __accept_Charset__3(now, req, fils = createFrere(fils))) {
        nbr++;
        now += len;
    }
    purgeFilsAndFrere(fils);
    purgeNode(fils);

    putValueInNode(p, now-p, "Accept_Charset", pere);
    return now-p;
}

int __accept_Charset__2(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = charset__OR__case(now, req, fils = createFils(pere)))) {
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

int charset__OR__case(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    if(len = charset(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = case_insensitive_char(p, req, fils, '*')) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeNode(fils);
        
    return false;
}

int charset(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = token(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "charset", pere);
    return now-p;
}

int __accept_Charset__3(int p, const char *req, node *pere)
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

    if(!(len = optional__accept_charset__3(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int optional__accept_charset__3(int p, const char *req, node *pere)
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

    if(!(len = __accept_Charset__2(now, req, fils))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}