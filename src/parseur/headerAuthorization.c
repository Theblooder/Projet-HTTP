#include <stdio.h>
#include <stdlib.h>
#include "../main/tree.h"
#include "subroutineMultipleTerminal.h"
#include "headerAuthorization.h"


#define true 1
#define false 0

int Authorization_header(int *p, const char *req, node *pere)
{
    int save = *p;

    if(case_insensitive_string(p, req, createFils(pere), "Authorization")) {
        if(case_insensitive_char(p, req, createFils(pere), ':')) {
            if(OWS(p, req, createFils(pere))) {
                if(Authorization(p, req, createFils(pere))) {
                    if(OWS(p, req, createFils(pere))) {
                        putValueInNode(save, *p-save, "Authorization_header", pere);
                        return true;
                    }
                }
            }
        }
    }

    *p = save;
    purgeFils(pere);
    return false;
}

int Authorization(int *p, const char *req, node *pere)
{
    int save = *p;

    if(credentials(p, req, createFils(pere))) {
        putValueInNode(save, *p-save, "Authorization", pere);
        return true;
    }

    *p = save;
    purgeFils(pere);
    return false;
}

int credentials(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;
    node *fils2;

    if(auth_scheme(p, req, fils = createFils(pere))) {
        int c = *p;
        int nbr = 0;
        while(1) {
            if(SP(p, req, fils2 = createFils(pere))) {
                nbr++;
                continue;
            }
            else {
                break;
            }
        }
        purgeNode(fils2);
        if(nbr >= 1) {
            fils2 = createFils(pere);
            if(token68(p, req, fils2)) {
                putValueInNode(save, *p-save, "credentials", pere);
                return true;
            }
            if(case_insensitive_char(p, req, fils2, ',') || auth_param(p, req, fils2)) {
                nbr = 0;
                int c2;
                node *fils4;
                node *fils5;
                while(1) {
                    c2 = *p;
                    if(OWS(p, req, fils4 = createFils(pere))) {
                        if(case_insensitive_char(p, req, createFils(pere), ',')) {
                            int c3 = *p;
                            if(OWS(p, req, fils5 = createFils(pere))) {
                                if(auth_param(p, req, createFils(pere))) {
                                    nbr++;
                                    continue;
                                }
                            }
                            *p = c3;
                            purgeNodeAndRightFrere(fils5);
                            nbr++;
                            continue;
                        }
                    }
                    purgeNodeAndRightFrere(fils4);
                    *p = c2;
                    break;
                }
                if(nbr >= 0) {
                    putValueInNode(save, *p-save, "credentials", pere);
                    return true;
                }
            }
        }
        if(fils->frere != NULL) {
            purgeNodeAndRightFrere(fils->frere);
        }
        *p = c;
        putValueInNode(save, *p-save, "credentials", pere);
        return true;
    }

    *p = save;
    purgeFils(pere);
    return false;
}

int auth_scheme(int *p, const char *req, node *pere)
{
    int save = *p;

    if(token(p, req, createFils(pere))) {
        putValueInNode(save, *p-save, "auth_scheme", pere);
        return true;
    }

    *p = save;
    purgeFils(pere);
    return false;
}

int token68(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;

    int nbr = 0;
    int c;
    while(1) {
        c = *p;
        fils = createFils(pere);

        if(ALPHA(p, req, fils)) {
            nbr++;
            continue;
        }
        else if(DIGIT(p, req, fils)) {
            nbr++;
            continue;
        }
        else if(case_insensitive_char(p, req, fils, '-')) {
            nbr++;
            continue;
        }
        else if(case_insensitive_char(p, req, fils, '.')) {
            nbr++;
            continue;
        }
        else if(case_insensitive_char(p, req, fils, '_')) {
            nbr++;
            continue;
        }
        else if(case_insensitive_char(p, req, fils, '~')) {
            nbr++;
            continue;
        }
        else if(case_insensitive_char(p, req, fils, '+')) {
            nbr++;
            continue;
        }
        else if(case_insensitive_char(p, req, fils, '/')) {
            nbr++;
            continue;
        }
        purgeNodeAndRightFrere(fils);
        *p = c;
        break;
    }
    if(nbr >= 1) {
        nbr = 0;
        while(1) {
            if(case_insensitive_char(p, req, fils = createFils(pere), '=')) {
                nbr++;
                continue;
            }
            else {
                break;
            }
        }
        purgeNode(fils);
        if(nbr >= 0) {
            putValueInNode(save, *p-save, "token68", pere);
            return true;
        }
    }

    *p = save;
    purgeFils(pere);
    return false;
}

int auth_param(int *p, const char *req, node *pere)
{
    int save = *p;

    if(token(p, req, createFils(pere))) {
        if(BWS(p, req, createFils(pere))) {
            if(case_insensitive_char(p, req, createFils(pere), '=')) {
                if(BWS(p, req, createFils(pere))) {
                    node *fils = createFils(pere);
                    if(token(p, req, fils) || quoted_string(p, req, fils)) {
                        putValueInNode(save, *p-save, "auth_param", pere);
                        return true;
                    }
                }
            }
        }
    }

    *p = save;
    purgeFils(pere);
    return false;
}