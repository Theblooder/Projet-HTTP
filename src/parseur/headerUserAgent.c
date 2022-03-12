#include <stdio.h>
#include <stdlib.h>
#include "../main/tree.h"
#include "subroutineMultipleTerminal.h"
#include "headerUserAgent.h"


#define true 1
#define false 0

int User_Agent_header(int *p, const char *req, node *pere)
{
    int save = *p;

    if(case_insensitive_string(p, req, createFils(pere), "User-Agent")) {
        if(case_insensitive_char(p, req, createFils(pere), ':')) {
            if(OWS(p, req, createFils(pere))) {
                if(User_Agent(p, req, createFils(pere))) {
                    if(OWS(p, req, createFils(pere))) {
                        putValueInNode(save, *p-save, "User_Agent_header", pere);
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

int User_Agent(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    if(product(p, req, createFils(pere))) {
        int nbr = 0;
        int c;
        while(1) {
            c = *p;

            if(RWS(p, req, fils = createFils(pere))) {
                node *fils2 = createFils(pere);
                if(product(p, req, fils2) || comment(p, req, fils2)) {
                    nbr++;
                    continue;
                }
            }
            purgeNodeAndRightFrere(fils);
            *p = c;
            break;
        }
        if(nbr >= 0) {
            putValueInNode(save, *p-save, "User_Agent", pere);
            return true;
        }
    }
    
    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int product(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    if(token(p, req, createFils(pere))) {
        int c = *p;
        if(case_insensitive_char(p, req, fils = createFils(pere), '/')) {
            if(product_version(p, req, createFils(pere))) {
                putValueInNode(save, *p-save, "product", pere);
                return true;
            }
        }
        *p = c;
        purgeNodeAndRightFrere(fils);
        putValueInNode(save, *p-save, "product", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int product_version(int *p, const char *req, node *pere)
{
    int save = *p;

    if(token(p, req, createFils(pere))) {
        putValueInNode(save, *p-save, "product_version", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int comment(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    if(case_insensitive_char(p, req, createFils(pere), '(')) {
        int nbr = 0;
        int c;
        while(1) {
            c = *p;
            fils = createFils(pere);

            if(ctext(p, req, fils)) {
                nbr++;
                continue;
            }
            else if(quoted_pair(p, req, fils)) {
                nbr++;
                continue;
            }
            else if(comment(p, req, fils)) {
                nbr++;
                continue;
            }
            purgeNodeAndRightFrere(fils);
            *p = c;
            break;
        }
        if(nbr >= 0) {
            if(case_insensitive_char(p, req, createFils(pere), ')')) {
                putValueInNode(save, *p-save, "comment", pere);
                return true;
            }
        }
    }
    
    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int ctext(int *p, const char *req, node *pere)
{
    int save = *p;

    node *fils = createFils(pere);

    if(HTAB(p, req, fils)) {
        putValueInNode(save, *p-save, "ctext", pere);
        return true;
    }
    else if(SP(p, req, fils)) {
        putValueInNode(save, *p-save, "ctext", pere);
        return true;
    }
    else if(range(p, req, fils, 0x21, 0x27)) {
        putValueInNode(save, *p-save, "ctext", pere);
        return true;
    }
    else if(range(p, req, fils, 0x2A, 0x5B)) {
        putValueInNode(save, *p-save, "ctext", pere);
        return true;
    }
    else if(range(p, req, fils, 0x5D, 0x7E)) {
        putValueInNode(save, *p-save, "ctext", pere);
        return true;
    }
    else if(obs_text(p, req, fils)) {
        putValueInNode(save, *p-save, "ctext", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}