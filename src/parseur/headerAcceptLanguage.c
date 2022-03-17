#include <stdio.h>
#include <stdlib.h>
#include "../main/tree.h"
#include "subroutineMultipleTerminal.h"
#include "headerAcceptLanguage.h"
#include "headerAccept.h"


#define true 1
#define false 0

int Accept_Language_header(int *p, const char *req, node *pere)
{
    int save = *p;

    if(case_insensitive_string(p, req, createFils(pere), "Accept-Language")) {
        if(case_insensitive_char(p, req, createFils(pere), ':')) {
            if(OWS(p, req, createFils(pere))) {
                if(Accept_Language(p, req, createFils(pere))) {
                    if(OWS(p, req, createFils(pere))) {
                        putValueInNode(save, *p-save, "Accept_Language_header", pere);
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

int Accept_Language(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils;
    node *fils2;
    node *fils3;

    int nbr = 0;
    int c;
    while(1) {
        c = *p;
        if(case_insensitive_char(p, req, fils = createFils(pere), ',')) {
            if(OWS(p, req, createFils(pere))) {
                nbr++;
                continue;
            }
        }
        purgeNodeAndRightFrere(fils);
        *p = c;
        break;
    }
    if(nbr >= 0) {
        if(language_range(p, req, createFils(pere))) {
            if(!weight(p, req, fils = createFils(pere))) {
                purgeNode(fils);
            }
            nbr = 0;
            while(1) {
                c = *p;
                if(OWS(p, req, fils = createFils(pere))) {
                    if(case_insensitive_char(p, req, createFils(pere), ',')) {
                        int c2 = *p;
                        if(OWS(p, req, fils2 = createFils(pere))) {
                            if(language_range(p, req, createFils(pere))) {
                                if(!weight(p, req, fils3 = createFils(pere))) {
                                    purgeNode(fils3);
                                }
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
                putValueInNode(save, *p-save, "Accept_Language", pere);
                return true;
            }
        }
    }

    *p = save;
    purgeFils(pere);
    return false;
}

int language_range(int *p, const char *req, node *pere)
{
    int save = *p;

    node *fils;
    node *fils2;

    if(case_insensitive_char(p, req, fils = createFils(pere), '*')) {
        putValueInNode(save, *p-save, "language_range", pere);
        return true;
    }
    else {
        purgeNode(fils);
        int nbr = 0;
        while(1) {
            if(ALPHA(p, req, fils = createFils(pere))) {
                nbr++;
                continue;
            }
            else {
                break;
            }
        }
        purgeNode(fils);
        if(nbr >= 1 && nbr <= 8) {
            nbr = 0;
            int c;
            while(1) {
                c = *p;

                if(case_insensitive_char(p, req, fils = createFils(pere), '-')) {
                    int nbr2 = 0;
                    while(1) {
                        if(alphanum(p, req, fils2 = createFils(pere))) {
                            nbr2++;
                            continue;
                        }
                        else {
                            break;
                        }
                    }
                    purgeNode(fils2);
                    if(nbr2 >= 1 && nbr2 <= 8) {
                        nbr++;
                        continue;
                    }
                }
                purgeNodeAndRightFrere(fils);
                *p = c;
                break;
            }
            if(nbr >= 0) {
                putValueInNode(save, *p-save, "language_range", pere);
                return true;
            }
        }
    }

    *p = save;
    purgeFils(pere);
    return false;
}

int alphanum(int *p, const char *req, node *pere)
{
    int save = *p;

    node *fils = createFils(pere);

    if(ALPHA(p, req, fils)) {
        putValueInNode(save, *p-save, "alphanum", pere);
        return true;
    }
    else if(DIGIT(p, req, fils)) {
        putValueInNode(save, *p-save, "alphanum", pere);
        return true;
    }

    *p = save;
    purgeFils(pere);
    return false;
}