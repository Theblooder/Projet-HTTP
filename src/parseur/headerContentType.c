#include <stdio.h>
#include <stdlib.h>
#include "../tree.h"
#include "subroutineMultipleTerminal.h"
#include "headerContentType.h"


#define true 1
#define false 0

int Content_Type_header(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_string(now, req, fils = createFils(pere), "Content-Type"))) {
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

    if(!(len = Content_Type(now, req, fils))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = OWS(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
    }
    now += len;

    putValueInNode(p, now-p, "Content_Type_header", pere);
    return now-p;
}

int Content_Type(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = media_type(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "Content_Type", pere);
    return now-p;
}

int media_type(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = type(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), '/'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = subtype(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    int nbr = 0;
    while(len = OWS__AND__case__AND__OWS__AND__parameter(now, req, fils = createFrere(fils))) {
        nbr++;
        now += len;
    }
    purgeFilsAndFrere(fils);
    purgeNode(fils);

    putValueInNode(p, now-p, "media_type", pere);
    return now-p;
}

int type(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = token(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "type", pere);
    return now-p;
}

int subtype(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = token(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "subtype", pere);
    return now-p;
}

int OWS__AND__case__AND__OWS__AND__parameter(int p, const char *req, node *pere)
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

    if(!(len = case_insensitive_char(now, req, fils, ';'))) {
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

    if(!(len = parameter(now, req, fils))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int parameter(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = token(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), '='))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = token__AND__quoted_string(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "parameter", pere);
    return now-p;
}