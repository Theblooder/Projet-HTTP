#include <stdio.h>
#include <stdlib.h>
#include "../main/tree.h"
#include "subroutineMultipleTerminal.h"
#include "headerAccept.h"
#include "headerContentType.h"


#define true 1
#define false 0

int Accept_header(int *p, const char *req, node *pere)
{
    int save = *p;

    if(case_insensitive_string(p, req, createFils(pere), "Accept")) {
        if(case_insensitive_char(p, req, createFils(pere), ':')) {
            if(OWS(p, req, createFils(pere))) {
                if(Accept(p, req, createFils(pere))) {
                    if(OWS(p, req, createFils(pere))) {
                        putValueInNode(save, *p-save, "Accept_header", pere);
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

int Accept(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils = createFils(pere);
    node *fils2;
    node *fils3;

    if(case_insensitive_char(p, req, fils, ',')) {
        1 == 1;
    }
    else if(media_range(p, req, fils)) {
        if(!accept_params(p, req, fils2 = createFils(pere))) {
            purgeNode(fils2);
        }
    }
    else {
        *p = save;
        purgeFilsAndFrere(pere);
        return true;
    }
    int nbr = 0;
    int c;
    while(1) {
        c = *p;
        if(OWS(p, req, fils = createFils(pere))) {
            if(case_insensitive_char(p, req, createFils(pere), ',')) {
                int c2 = *p;
                if(OWS(p, req, fils2 = createFils(pere))) {
                    if(media_range(p, req, createFils(pere))) {
                        if(accept_params(p, req, fils3 = createFils(pere))) {
                            nbr++;
                            continue;
                        }
                        purgeNode(fils3);
                        nbr++;
                        continue;
                    }
                }
                *p = c2;
                purgeNodeAndRightFrere(fils2);
                nbr++;
                continue;
            }
        }
        purgeNodeAndRightFrere(fils);
        *p = c;
        break;
    }
    if(nbr >= 0) {
        putValueInNode(save, *p-save, "Accept", pere);
        return true;
    }
}

int media_range(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;
    int pass = 0;

    if(case_insensitive_string(p, req, fils = createFils(pere), "*/*")) {
        pass = 1;
    }
    if(!pass && type(p, req, fils = createFils(pere))) {
        if(case_insensitive_char(p, req, createFils(pere), '/')) {
            if(subtype(p, req, createFils(pere))) {
                pass = 1;
            }
        }
    }
    if(!pass) {
        *p = save;
        purgeNodeAndRightFrere(fils);
        if(type(p, req, createFils(pere))) {
            if(case_insensitive_string(p, req, createFils(pere), "/*")) {
                pass = 1;
            }
        }
    }

    if(pass) {
        int nbr = 0;
        int c;
        while(1) {
            c = *p;

            if(OWS(p, req, fils = createFils(pere))) {
                if(case_insensitive_char(p, req, createFils(pere), ';')) {
                    if(OWS(p, req, createFils(pere))) {
                        if(parameter(p, req, createFils(pere))) {
                            nbr++;
                            continue;
                        }
                    }
                }
            }
            purgeNodeAndRightFrere(fils);
            *p = c;
            break;
        }
        if(nbr >= 0) {
            putValueInNode(save, *p-save, "media_range", pere);
            return true;
        }
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int accept_params(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    if(weight(p, req, createFils(pere))) {
        int nbr = 0;
        while(1) {
            if(accept_ext(p, req, fils = createFils(pere))) {
                nbr++;
                continue;
            }
            else {
                break;
            }
        }
        purgeNode(fils);
        if(nbr >= 0) {
            putValueInNode(save, *p-save, "accept_params", pere);
            return true;
        }
    }
    
    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int weight(int *p, const char *req, node *pere)
{
    int save = *p;

    if(OWS(p, req, createFils(pere))) {
        if(case_insensitive_char(p, req, createFils(pere), ';')) {
            if(OWS(p, req, createFils(pere))) {
                if(case_insensitive_string(p, req, createFils(pere), "q=")) {
                    if(qvalue(p, req, createFils(pere))) {
                        putValueInNode(save, *p-save, "weight", pere);
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

int qvalue(int *p, const char *req, node *pere)
{
    int save = *p;

    node *fils;
    node *fils2;

    int nbr = 0;
    int c;

    if(case_insensitive_char(p, req, createFils(pere), '0')) {
        c = *p;
        if(case_insensitive_char(p, req, fils = createFils(pere), '.')) {
            while(1) {
                if(DIGIT(p, req, fils2 = createFils(pere))) {
                    nbr++;
                    continue;
                }
                else {
                    break;
                }
            }
            purgeNode(fils2);
            if(nbr <= 3) {
                putValueInNode(save, *p-save, "qvalue", pere);
                return true;
            }
        }
        *p = c;
        purgeNodeAndRightFrere(fils);
        putValueInNode(save, *p-save, "qvalue", pere);
        return true;
    }
    *p = save;
    purgeFilsAndFrere(pere);
    nbr = 0;
    if(case_insensitive_char(p, req, createFils(pere), '1')) {
        c = *p;
        if(case_insensitive_char(p, req, fils = createFils(pere), '.')) {
            while(1) {
                if(case_insensitive_char(p, req, fils2 = createFils(pere), '0')) {
                    nbr++;
                    continue;
                }
                else {
                    break;
                }
            }
            purgeNode(fils2);
            if(nbr <= 3) {
                putValueInNode(save, *p-save, "qvalue", pere);
                return true;
            }
        }
        *p = c;
        purgeNodeAndRightFrere(fils);
        putValueInNode(save, *p-save, "qvalue", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int accept_ext(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    if(OWS(p, req, createFils(pere))) {
        if(case_insensitive_char(p, req, createFils(pere), ';')) {
            if(OWS(p, req, createFils(pere))) {
                if(token(p, req, createFils(pere))) {
                    int c = *p;
                    if(case_insensitive_char(p, req, fils = createFils(pere), '=')) {
                        node *fils2 = createFils(pere);
                        if(token(p, req, fils2) || quoted_string(p, req, fils2)) {
                            putValueInNode(save, *p-save, "accept_ext", pere);
                            return true;
                        }
                    }
                    *p = c;
                    purgeNodeAndRightFrere(fils);
                    putValueInNode(save, *p-save, "accept_ext", pere);
                    return true;
                }
            }
        }
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}