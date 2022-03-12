#include <stdio.h>
#include <stdlib.h>
#include "../main/tree.h"
#include "subroutineParseur.h"
#include "subroutineMultipleTerminal.h"
#include "subroutineFirstLine.h"


#define true 1
#define false 0



int start_line(int *p, const char *req, node *pere)
{
    int save = *p;

    node *fils = createFils(pere);

    if(request_line(p, req, fils)) {
        putValueInNode(save, *p-save, "start_line", pere);
        return true;
    }
    else if(request_target(p, req, fils)) {
        putValueInNode(save, *p-save, "start_line", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int request_line(int *p, const char *req, node *pere)
{
    int save = *p;

    if(method(p, req, createFils(pere))) {
        if(SP(p, req, createFils(pere))) {
            if(request_target(p, req, createFils(pere))) {
                if(SP(p, req, createFils(pere))) {
                    if(HTTP_version(p, req, createFils(pere))) {
                        if(CRLF(p, req, createFils(pere))) {
                            putValueInNode(save, *p-save, "request_line", pere);
                            return true;
                        }
                    }
                }
            }
        }
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int method(int *p, const char *req, node *pere)
{
    int save = *p;

    if(token(p, req, createFils(pere))) {
        putValueInNode(save, *p-save, "method", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int request_target(int *p, const char *req, node *pere)
{
    int save = *p;

    if(origin_form(p, req, createFils(pere))) {
        putValueInNode(save, *p-save, "request_target", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int origin_form(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    if(absolute_path(p, req, createFils(pere))) {
        int c = *p;
        if(case_insensitive_char(p, req, fils = createFils(pere), '?')) {
            if(query(p, req, createFils(pere))) {
                putValueInNode(save, *p-save, "origin_form", pere);
                return true;
            }
        }
        *p = c;
        purgeNodeAndRightFrere(fils);
        putValueInNode(save, *p-save, "origin_form", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int absolute_path(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    int nbr = 0;
    int c;
    while(1) {
        c = *p;

        if(case_insensitive_char(p, req, fils = createFils(pere), '/')) {
            if(segment(p, req, createFils(pere))) {
                nbr++;
                continue;
            }
        }
        purgeNodeAndRightFrere(fils);
        *p = c;
        break;
    }
    if(nbr >= 1) {
        putValueInNode(save, *p-save, "absolute_path", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int query(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    int nbr = 0;
    int c;
    while(1) {
        c = *p;
        fils = createFils(pere);

        if(pchar(p, req, fils)) {
            nbr++;
            continue;
        }
        else if(case_insensitive_char(p, req, fils, '/')) {
            nbr++;
            continue;
        }
        else if(case_insensitive_char(p, req, fils, '?')) {
            nbr++;
            continue;
        }
        purgeNodeAndRightFrere(fils);
        *p = c;
        break;
    }
    if(nbr >= 1) {
        putValueInNode(save, *p-save, "query", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return true;
}

int HTTP_version(int *p, const char *req, node *pere)
{
    int save = *p;

    if(HTTP_name(p, req, createFils(pere))) {
        if(case_insensitive_char(p, req, createFils(pere), '/')) {
            if(DIGIT(p, req, createFils(pere))) {
                if(case_insensitive_char(p, req, createFils(pere), '.')) {
                    if(DIGIT(p, req, createFils(pere))) {
                        putValueInNode(save, *p-save, "HTTP_version", pere);
                        return true;
                    }
                }
            }
        }
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int HTTP_name(int *p, const char *req, node *pere)
{
    int save = *p;
    int v[4] = {0x48, 0x54, 0x54, 0x50};

    if(num(p, req, createFils(pere), v, 4)) {
        putValueInNode(save, *p-save, "HTTP_name", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int status_line(int *p, const char *req, node *pere)
{
    int save = *p;

    if(HTTP_version(p, req, createFils(pere))) {
        if(SP(p, req, createFils(pere))) {
            if(status_code(p, req, createFils(pere))) {
                if(SP(p, req, createFils(pere))) {
                    if(reason_phrase(p, req, createFils(pere))) {
                        if(CRLF(p, req, createFils(pere))) {
                            putValueInNode(save, *p-save, "status_line", pere);
                            return true;
                        }
                    }
                }
            }
        }
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int status_code(int *p, const char *req, node *pere)
{
    int save = *p;

    int nbr = 0;
    node *fils;
    while(1) {
        if(DIGIT(p, req, fils = createFils(pere))) {
            nbr++;
            continue;
        }
        else {
            break;
        }
    }
    purgeNode(fils);
    if(nbr == 3) {
        putValueInNode(save, *p-save, "status_code", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int reason_phrase(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    int nbr = 0;
    int c;
    while(1) {  
        c = *p;
        fils = createFils(pere);

        if(HTAB(p, req, fils)) {
            nbr++;
            continue;
        }
        else if(SP(p, req, fils)) {
            nbr++;
            continue;
        }
        else if(VCHAR(p, req, fils)) {
            nbr++;
            continue;
        }
        else if(obs_text(p, req, fils)) {
            nbr++;
            continue;
        }
        purgeNodeAndRightFrere(fils);
        *p = c;
        break;
    }
    if(nbr >= 1) {
        putValueInNode(save, *p-save, "reason_phrase", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return true;
}