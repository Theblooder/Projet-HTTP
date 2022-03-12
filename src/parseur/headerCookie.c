#include <stdio.h>
#include <stdlib.h>
#include "../main/tree.h"
#include "subroutineMultipleTerminal.h"
#include "headerCookie.h"


#define true 1
#define false 0

int Cookie_header(int *p, const char *req, node *pere)
{
    int save = *p;

    if(case_insensitive_string(p, req, createFils(pere), "Cookie:")) {
        if(OWS(p, req, createFils(pere))) {
            if(cookie_string(p, req, createFils(pere))) {
                if(OWS(p, req, createFils(pere))) {
                    putValueInNode(save, *p-save, "Cookie_header", pere);
                    return true;
                }
            }
        }
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int cookie_string(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    if(cookie_pair(p, req, createFils(pere))) {
        int nbr = 0;
        int c;
        while(1) {
            c = *p;

            if(case_insensitive_char(p, req, fils = createFils(pere), ';')) {
                if(SP(p, req, createFils(pere))) {
                    if(cookie_pair(p, req, createFils(pere))) {
                        nbr++;
                        continue;
                    }
                }
            }
            purgeNodeAndRightFrere(fils);
            *p = c;
            break;
        }
        if(nbr >= 0) {
            putValueInNode(save, *p-save, "cookie_string", pere);
            return true;
        }
    }
    
    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int cookie_pair(int *p, const char *req, node *pere)
{
    int save = *p;

    if(cookie_name(p, req, createFils(pere))) {
        if(case_insensitive_char(p, req, createFils(pere), '=')) {
            if(cookie_value(p, req, createFils(pere))) {
                putValueInNode(save, *p-save, "cookie_pair", pere);
                return true;
            }
        }
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int cookie_name(int *p, const char *req, node *pere)
{
    int save = *p;

    if(token(p, req, createFils(pere))) {
        putValueInNode(save, *p-save, "cookie_name", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int cookie_value(int *p, const char *req, node *pere)
{
    int save = *p;

    node *fils;

    if(DQUOTE(p, req, fils = createFils(pere))) {
        int nbr = 0;
        node *fils2;
        while(1) {
            if(cookie_octet(p, req, fils2 = createFils(pere))) {
                nbr++;
                continue;
            }
            else {
                break;
            }
        }
        purgeNode(fils2);
        if(nbr >= 0) {
            if(DQUOTE(p, req, createFils(pere))) {
                putValueInNode(save, *p-save, "cookie_value", pere);
                return true;
            }
        }
    }
    else if(1 == 1) {
        purgeNodeAndRightFrere(fils);
        int nbr = 0;
        node *fils2;
        while(1) {
            if(cookie_octet(p, req, fils2 = createFils(pere))) {
                nbr++;
                continue;
            }
            else {
                break;
            }
        }
        purgeNode(fils2);
        if(nbr >= 1) {
            putValueInNode(save, *p-save, "cookie_value", pere);
            return true;
        }
        else {
            return true;
        }
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int cookie_octet(int *p, const char *req, node *pere)
{
    int save = *p;

    node *fils = createFils(pere);

    int v[1] = {0x21};
    if(num(p, req, fils, v, 1)) {
        putValueInNode(save, *p-save, "cookie_octet", pere);
        return true;
    }
    else if(range(p, req, fils, 0x23, 0x2B)) {
        putValueInNode(save, *p-save, "cookie_octet", pere);
        return true;
    }
    else if(range(p, req, fils, 0x2D, 0x3A)) {
        putValueInNode(save, *p-save, "cookie_octet", pere);
        return true;
    }
    else if(range(p, req, fils, 0x3C, 0x5B)) {
        putValueInNode(save, *p-save, "cookie_octet", pere);
        return true;
    }
    else if(range(p, req, fils, 0x5D, 0x7E)) {
        putValueInNode(save, *p-save, "cookie_octet", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}