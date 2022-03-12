#include <stdio.h>
#include <stdlib.h>
#include "../main/tree.h"
#include "subroutineMultipleTerminal.h"
#include "headerAcceptEncoding.h"
#include "headerAccept.h"


#define true 1
#define false 0

int Accept_Encoding_header(int *p, const char *req, node *pere)
{
    int save = *p;

    if(case_insensitive_string(p, req, createFils(pere), "Accept-Encoding")) {
        if(case_insensitive_char(p, req, createFils(pere), ':')) {
            if(OWS(p, req, createFils(pere))) {
                if(Accept_Encoding(p, req, createFils(pere))) {
                    if(OWS(p, req, createFils(pere))) {
                        putValueInNode(save, *p-save, "Accept_Encoding_header", pere);
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

int Accept_Encoding(int *p, const char *req, node *pere)
{
    int save = *p;
    node *fils = createFils(pere);
    node *fils2;
    node *fils3;

    if(case_insensitive_char(p, req, fils, ',')) {
        1 == 1;
    }
    else if(codings(p, req, fils)) {
        if(!weight(p, req, fils2 = createFils(pere))) {
            purgeNode(fils2);
        }
    }
    else {
        *p = save;
        purgeFilsAndFrere(pere);
        putValueInNode(save, *p-save, "Accept_Encoding", pere);
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
                    if(codings(p, req, createFils(pere))) {
                        if(weight(p, req, fils3 = createFils(pere))) {
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
        putValueInNode(save, *p-save, "Accept_Encoding", pere);
        return true;
    }
}

int codings(int *p, const char *req, node *pere)
{
    int save = *p;

    node *fils = createFils(pere);

    if(content_coding(p, req, fils)) {
        putValueInNode(save, *p-save, "codings", pere);
        return true;
    }
    else if(case_insensitive_string(p, req, fils, "identity")) {
        putValueInNode(save, *p-save, "codings", pere);
        return true;
    }
    else if(case_insensitive_char(p, req, fils, '*')) {
        putValueInNode(save, *p-save, "codings", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}

int content_coding(int *p, const char *req, node *pere)
{
    int save = *p;

    if(token(p, req, createFils(pere))) {
        putValueInNode(save, *p-save, "content_coding", pere);
        return true;
    }

    *p = save;
    purgeFilsAndFrere(pere);
    return false;
}