#include <stdio.h>
#include <stdlib.h>
#include "../tree.h"
#include "subroutineMultipleTerminal.h"
#include "headerAccept.h"
#include "headerContentType.h"


#define true 1
#define false 0

int Accept_header(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_string(now, req, fils = createFils(pere), "Accept"))) {
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

    if(!(len = Accept(now, req, fils))) {
        purgeFilsAndFrere(fils);
    }
    else {
        fils = createFrere(fils);
    }
    now += len;

    if(!(len = OWS(now, req, fils))) {
        purgeNode(fils);
    }
    now += len;

    putValueInNode(p, now-p, "Accept_header", pere);
    return now-p;
}

int Accept(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = __accept__1(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    int nbr = 0;
    while(len = __accept__2(now, req, fils = createFrere(fils))) {
        nbr++;
        now += len;
    }
    purgeFilsAndFrere(fils);
    purgeNode(fils);

    putValueInNode(p, now-p, "Accept_header", pere);
    return now-p;
}

int __accept__1(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    if(len = case_insensitive_char(p, req, fils = createFils(pere), ',')) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = media_range__AND__accept_params(p, req, fils)) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeNode(fils);
        
    return false;
}

int media_range__AND__accept_params(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = media_range(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = accept_params(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int media_range(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = __media_range__1(now, req, fils = createFils(pere)))) {
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

    putValueInNode(p, now-p, "media_range", pere);
    return now-p;
}

int __media_range__1(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    if(len = case_insensitive_string(p, req, fils = createFils(pere), "*/*")) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = type__AND__case__AND__subtype(p, req, fils)) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = type__AND__case(p, req, fils)) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeNode(fils);
        
    return false;
}

int type__AND__case__AND__subtype(int p, const char *req, node *pere)
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

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int type__AND__case(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = type(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_string(now, req, fils = createFrere(fils), "/*"))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int accept_params(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = weight(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    int nbr = 0;
    while(len = accept_ext(now, req, fils = createFrere(fils))) {
        nbr++;
        now += len;
    }
    purgeFilsAndFrere(fils);
    purgeNode(fils);

    putValueInNode(p, now-p, "accept_params", pere);
    return now-p;
}

int weight(int p, const char *req, node *pere)
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

    if(!(len = case_insensitive_string(now, req, fils, "q="))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = qvalue(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "weight", pere);
    return now-p;
}

int qvalue(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    if(len = qvalue__1(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "qvalue", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = qvalue__2(p, req, fils)) {
        putValueInNode(p, len, "qvalue", pere);
        return len;
    }
    else
        purgeNode(fils);
        
    return false;
}

int qvalue__1(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_char(now, req, fils = createFils(pere), '0'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = optional__case__AND__3DIGITS(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int optional__case__AND__3DIGITS(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_char(now, req, fils = createFils(pere), '.'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    int nbr = 0;
    while(len = DIGIT(now, req, fils = createFrere(fils))) {
        nbr++;
        now += len;
    }
    purgeFilsAndFrere(fils);
    purgeNode(fils);
    if(nbr > 3) {
        return false;
    }

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int qvalue__2(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_char(now, req, fils = createFils(pere), '1'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = optional__case__AND__3ZERO(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int optional__case__AND__3ZERO(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_char(now, req, fils = createFils(pere), '.'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    int nbr = 0;
    while(len = case_insensitive_char(now, req, fils = createFrere(fils), '0')) {
        nbr++;
        now += len;
    }
    purgeFilsAndFrere(fils);
    purgeNode(fils);
    if(nbr > 3) {
        return false;
    }

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int accept_ext(int p, const char *req, node *pere)
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

    if(!(len = token(now, req, fils))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = optional__case__AND__token__AND__case__quoted_string(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
    }
    now += len;

    putValueInNode(p, now-p, "accept_ext", pere);
    return now-p;
}

int optional__case__AND__token__AND__case__quoted_string(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_char(now, req, fils = createFils(pere), '='))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = token__AND__quoted_string(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int __accept__2(int p, const char *req, node *pere)
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

    if(!(len = optional__accept__2(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int optional__accept__2(int p, const char *req, node *pere)
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

    if(!(len = media_range__AND__accept_params(now, req, fils))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}