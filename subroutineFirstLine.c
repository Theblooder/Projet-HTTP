#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "subroutineParseur.h"
#include "subroutineMultipleTerminal.h"
#include "subroutineFirstLine.h"


#define true 1
#define false 0



int start_line(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    if(len = request_line(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "start_line", pere);
        return len;
    }
    else
        purgeNode(fils);

    if(len = status_line(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "start_line", pere);
        return len;
    }
    else
        purgeNode(fils);
        
    return false;
}

int request_line(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = method(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = SP(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = request_target(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = SP(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = HTTP_version(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = CRLF(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "request_line", pere);
    return now-p;
}

int method(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = token(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "method", pere);
    return now-p;
}

int request_target(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = origin_form(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "request_target", pere);
    return now-p;
}

int origin_form(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = absolute_path(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case__AND__query(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
    }
    now += len;

    putValueInNode(p, now-p, "origin_form", pere);
    return now-p;
}

int absolute_path(int p, const char *req, node *pere)
{
    int len;
    int now = p;
    node *fils;

    int nbr = 0;
    fils = createFils(pere);
    while(len = case__AND__segment(now, req, fils)) {
        nbr++;
        now += len;
        fils = createFrere(fils);
    }
    purgeFilsAndFrere(fils);
    purgeNode(fils);
    if(nbr < 1) {
        return false;
    }
    
    putValueInNode(p, now-p, "absolute_path", pere);
    return now-p;
}

int case__AND__segment(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_char(now, req, fils = createFils(pere), '/'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = segment(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int case__AND__query(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = case_insensitive_char(now, req, fils = createFils(pere), '?'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = query(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "", pere);
    return now-p;
}

int query(int p, const char *req, node *pere)
{
    int len;
    int now = p;
    node *fils;

    int nbr = 0;
    fils = createFils(pere);
    while(len = pchar__AND__cases(now, req, fils)) {
        nbr++;
        now += len;
        fils = createFrere(fils);
    }
    purgeFilsAndFrere(fils);
    purgeNode(fils);
    
    putValueInNode(p, now-p, "query", pere);
    return now-p;
}

int pchar__AND__cases(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    if(req[p] != '\0') {
        if(req[p] == '/') {
            putValueInNode(p, 1, "case_insensitive_string", pere);
            return 1;
        }
        else if(req[p] == '?') {
            putValueInNode(p, 1, "case_insensitive_string", pere);
            return 1;
        }
    }
    else
        return false;

    if(len = pchar(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeNode(fils);
    
    return false;
}

int HTTP_version(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = HTTP_name(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), '/'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = DIGIT(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = case_insensitive_char(now, req, fils = createFrere(fils), '.'))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = DIGIT(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "HTTP_version", pere);
    return now-p;
}

int HTTP_name(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    int v[4] = {0x48, 0x54, 0x54, 0x50};
    if(!(len = num(now, req, fils = createFils(pere), v, 4))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "HTTP_name", pere);
    return now-p;
}

int status_line(int p, const char *req, node *pere)
{
    int len;
    int now = p;

    node* fils;

    if(!(len = HTTP_version(now, req, fils = createFils(pere)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = SP(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = status_code(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = SP(now, req, fils = createFrere(fils)))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    if(!(len = reason_phrase(now, req, fils = createFrere(fils)))) {
        purgeFilsAndFrere(fils);
    }
    else {
        fils = createFrere(fils);
    }
    now += len;

    if(!(len = CRLF(now, req, fils))) {
        purgeNode(fils);
        return false;
    }
    now += len;

    putValueInNode(p, now-p, "status_line", pere);
    return now-p;
}

int status_code(int p, const char *req, node *pere)
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
    if(nbr != 3) {
        return false;
    }
    
    putValueInNode(p, now-p, "status_code", pere);
    return now-p;
}

int reason_phrase(int p, const char *req, node *pere)
{
    int len;
    int now = p;
    node *fils;

    int nbr = 0;
    fils = createFils(pere);
    while(len = __reason_phrase__(now, req, fils)) {
        nbr++;
        now += len;
        fils = createFrere(fils);
    }
    purgeFilsAndFrere(fils);
    purgeNode(fils);
    
    putValueInNode(p, now-p, "reason_phrase", pere);
    return now-p;
}

int __reason_phrase__(int p, const char *req, node *pere)
{
    int len;
    node *fils;

    if(len = HTAB(p, req, fils = createFils(pere))) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = SP(p, req, fils)) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);

    if(len = VCHAR(p, req, fils)) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeFilsAndFrere(fils);
    
    if(len = obs_text(p, req, fils)) {
        putValueInNode(p, len, "", pere);
        return len;
    }
    else
        purgeNode(fils);
        
    return false;
}