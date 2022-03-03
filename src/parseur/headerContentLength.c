#include <stdio.h>
#include <stdlib.h>
#include "../main/tree.h"
#include "subroutineMultipleTerminal.h"
#include "headerContentLength.h"


#define true 1
#define false 0

int Content_Length_Header(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_string(now, req, fils = createFils(pere), "Content-Length"))) {
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

    if(!(len = Content_Length(now, req, fils))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = OWS(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
    }
    now += len;

    putValueInNode(p, now-p, "Content_Length_Header", pere);
    return now-p;
}

int Content_Length(int p, const char *req, node *pere)
{
    int len;
    int now = p;
    node *fils;

    int nbr = 0;
    fils = createFils(pere);
    while(len = DIGIT(now, req, fils)) {
        nbr++;
        now += len;
        fils = createFrere(fils);
    }
    purgeFilsAndFrere(fils);
    purgeNode(fils);
    if(nbr == 0) {
        return false;
    }
    
    putValueInNode(p, now-p, "Content_Length", pere);
    return now-p;
}