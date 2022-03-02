#include <stdio.h>
#include <stdlib.h>
#include "../tree.h"
#include "subroutineMultipleTerminal.h"
#include "headerCookie.h"


#define true 1
#define false 0

int Cookie_header(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_string(now, req, fils = createFils(pere), "Cookie:"))) {
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

    if(!(len = cookie_string(now, req, fils))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = OWS(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
    }
    now += len;

    putValueInNode(p, now-p, "Cookie_header", pere);
    return now-p;
}

int cookie_string(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = cookie_pair(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    int nbr = 0;
    while(len = case__AND__SP__AND__cookie_pair(now, req, fils = createFrere(fils))) {
        nbr++;
        now += len;
    }
    purgeFilsAndFrere(fils);
    purgeNode(fils);

    putValueInNode(p, now-p, "cookie_string", pere);
    return now-p;
}

int cookie_pair(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = cookie_name(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), '='))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = cookie_value(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "cookie_pair", pere);
    return now-p;
}

int cookie_name(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = token(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "cookie_name", pere);
    return now-p;
}

int cookie_value(int p, const char *req, node *pere)
{
    int len;
    int now = p;
    node *fils;

    if(len = DQUOTE__AND__cookie_octet__AND__DQUOTE(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "cookie_value", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    int nbr = 0;
    while(len = cookie_octet(now, req, fils)) {
        nbr++;
        now += len;
        fils = createFrere(fils);
    }
    purgeFilsAndFrere(fils);
    purgeNode(fils);

    if(now-p != 0)
        putValueInNode(p, now-p, "cookie_value", pere);
    return now-p;
}

int DQUOTE__AND__cookie_octet__AND__DQUOTE(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = DQUOTE(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    int nbr = 0;
    while(len = cookie_octet(now, req, fils = createFrere(fils))) {
        nbr++;
        now += len;
    }
    purgeFilsAndFrere(fils);

    if(!(len = DQUOTE(now, req, fils))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int cookie_octet(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    int v[1] = {0x21};
    if(len = num(p, req, fils = createFils(pere), v, 1)) {
        putValueInNode(p, len, "cookie_octet", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = range(p, req, fils, 0x23, 0x2B)) {
        putValueInNode(p, len, "cookie_octet", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = range(p, req, fils, 0x2D, 0x3A)) {
        putValueInNode(p, len, "cookie_octet", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = range(p, req, fils, 0x3C, 0x5B)) {
        putValueInNode(p, len, "cookie_octet", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = range(p, req, fils, 0x5D, 0x7E)) {
        putValueInNode(p, len, "cookie_octet", pere);
        return len;
    }
    else
        purgeNode(fils);
        
    return false;
}

int case__AND__SP__AND__cookie_pair(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_char(now, req, fils = createFils(pere), ';'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = SP(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = cookie_pair(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}